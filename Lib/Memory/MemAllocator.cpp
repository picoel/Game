/**
  * @file	MemAllocator.cpp
  * @brief	メモリアロケーター
  * @date	2015/04/18 11:50:31
  */

#include "Lib/LibPrecompile.h"

#include <new>
#include "Lib/Memory/MemAllocator.h"
#include "Lib/Memory/MemBlock.h"
#include "Lib/Math/Bit.h"

#if defined( USE_MEMORY_DEBUG )
#define MEM_ASSERT(I) ASSERT(I)
#else // #if defined( USE_MEMORY_DEBUG )
#define MEM_ASSERT(I)
#endif // #else // #if defined( USE_MEMORY_DEBUG )

namespace
{
	const U32 sc_uPartitionNumArray[ CMemAllocator::StInitParam::enPartitionNum_Max ] =
	{
		1,
		2,
		4,
		8,
		16,
		32,
	};
};

/**
 * @brief		コンストラクタ。
 * @param[in]	_rstInitParam	: 初期化用パラメータ
 */
CMemAllocator::CMemAllocator( const StInitParam& _rstInitParam )
	: m_stInitParam()
	, m_pMemory( nullptr )
	, m_pFreeBlockArray( nullptr )
	, m_uIsFree( 0 )
	, m_cCriticalSection()
#if defined( USE_MEMORY_DEBUG )
	, m_stDebugMemoryInfo()
#endif // #if defined( USE_MEMORY_DEBUG )
{
	MemCopy( &m_stInitParam, &_rstInitParam, sizeof( m_stInitParam ) );

	m_pMemory = s_cast<U8*>( malloc( _rstInitParam.m_uSize ) );
	memset( m_pMemory, 0xCCCCCCCC, m_stInitParam.m_uSize );

	for (U32 ii = 0; ii < lengthof( m_uIsFreeArray ); ++ii)
	{
		m_uIsFreeArray[ ii ] = 0;
	}

	// 確保したメモリの先頭にフリーリストを作成。
	const USize uFreeListSize = enFirstLevel_Max * sc_uPartitionNumArray[m_stInitParam.m_ePartition];
	const USize uFreeListBlockSize = GetBlockSize( sizeof( CMemBlock** ) * uFreeListSize );
	CMemBlock* pcFreeListMemBlock = new( m_pMemory ) CMemBlock( uFreeListBlockSize );
	pcFreeListMemBlock->SetUsed( true );
	m_pFreeBlockArray = s_cast<CMemBlock**>( pcFreeListMemBlock->GetData() );
	for (U32 ii = 0; ii < uFreeListSize; ++ii)
	{
		m_pFreeBlockArray[ ii ] = nullptr;
	}

	// マージの際に領域を超えないように、終端にダミーを置く。
	const USize uDummyBlockSize = GetBlockSize( 0 );
	m_pEndBlock = new( m_pMemory + m_stInitParam.m_uSize - uDummyBlockSize ) CMemBlock( uDummyBlockSize );
	m_pEndBlock->SetUsed( true );

	CMemBlock* pcMemBlock = new( pcFreeListMemBlock->GetNextBlock() )CMemBlock( m_stInitParam.m_uSize - uFreeListBlockSize - uDummyBlockSize );
	SetFreeList( pcMemBlock );

#if defined( USE_MEMORY_DEBUG )
	const USize uUsedSize = pcFreeListMemBlock->GetBlockSize() + m_pEndBlock->GetBlockSize();
	InitDebugInfo( m_stInitParam.m_uSize, uUsedSize );
#endif // #if defined( USE_MEMORY_DEBUG )
}

/**
 * @brief	デストラクタ。
 */
CMemAllocator::~CMemAllocator()
{
	free( m_pMemory );
}

/**
 * @brief		メモリを確保。
 * @param[in]	_uSize	: 確保するサイズ。
 * @param[in]	_psFile	: 呼び出し元のファイル名。
 * @param[in]	_uLine	: 呼び出し元行数。
 * @return				: 確保したメモリへのポインタ。
 */
void* CMemAllocator::Alloc( USize _uSize, const S8* _psFile, U32 _uLine )
{
	CCriticalSectionBlock cCSBlock ( &m_cCriticalSection );

	#if defined( USE_MEMORY_DEBUG )
	MEM_ASSERT( 0 < _uSize );
	if (_uSize <= 0)
	{
		return nullptr; // failsafe
	}

	MEM_ASSERT( _uSize < m_stInitParam.m_uSize );
	if (m_stInitParam.m_uSize <= _uSize)
	{
		return nullptr; // failsafe
	}
	#endif // #if defined( USE_MEMORY_DEBUG )

	const USize uBlockSize = GetBlockSize( _uSize );

	U32 uFirstLevel = 0;
	U32 uSecondLevel = 0;

	void* pRet = nullptr;
	if (SearchFreeListLevel( &uFirstLevel, &uSecondLevel, uBlockSize ))
	{
		const U32 uIndex = GetFreeListIndex( uFirstLevel, uSecondLevel );
		CMemBlock* pcMemBlock = m_pFreeBlockArray[ uIndex ];
		MEM_ASSERT( pcMemBlock );
		if (pcMemBlock)
		{
			 MEM_ASSERT( uBlockSize <= pcMemBlock->GetBlockSize() );
			 MEM_ASSERT( !pcMemBlock->IsUsed() );
			if (!pcMemBlock->IsUsed())
			{
				pRet = AllocFromMemBlock( pcMemBlock, _uSize, _psFile, _uLine, EnAllocMode::enForward );
			}
		}
	}

	return pRet;
}

/**
 * @brief		最後尾からメモリを確保。
 * @param[in]	_uSize	: 確保するサイズ。
 * @param[in]	_psFile	: 呼び出し元のファイル名。
 * @param[in]	_uLine	: 呼び出し元行数。
 * @return				: 確保したメモリへのポインタ。
 */
void* CMemAllocator::AllocBack( USize _uSize, const S8* _psFile, U32 _uLine )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	#if defined( USE_MEMORY_DEBUG )
	MEM_ASSERT( 0 < _uSize );
	if (_uSize <= 0)
	{
		return nullptr;	// failsafe
	}

	MEM_ASSERT( _uSize < m_stInitParam.m_uSize );
	if (m_stInitParam.m_uSize <= _uSize)
	{
		return nullptr;	// failsafe
	}

	MEM_ASSERT( m_pEndBlock );
	if (nullptr == m_pEndBlock)
	{
		return nullptr;	// failsafe
	}
	#endif // #if defined( USE_MEMORY_DEBUG )

	const USize uBlockSize = GetBlockSize( _uSize );

	// 後ろからメモリを確保出来るメモリブロックを探す。
	CMemBlock* pcMemBlock = m_pEndBlock->GetPrevBlock();
	CMemBlock* pcFindMemBlock = nullptr;
	while (s_cast<void*>(m_pMemory) < s_cast<void*>(pcMemBlock))
	{
		if (pcMemBlock->IsUsed())
		{
			// 使用中ならば確保出来ない。
		}
		else if (pcMemBlock->GetBlockSize() < _uSize)
		{
			// サイズが足りなければ使用出来ない。
		}
		else
		{
			// 使用可能。
			pcFindMemBlock = pcMemBlock;
			break;
		}

		pcMemBlock = pcMemBlock->GetPrevBlock();
	}

	void* pRet = nullptr;
	if (pcFindMemBlock)
	{
		pRet = AllocFromMemBlock( pcFindMemBlock, _uSize, _psFile, _uLine, EnAllocMode::enBack );
	}

	return pRet;
}

/**
 * @brief	指定したメモリブロックからメモリを確保。
 * @param[in]	_pcMemBlock	; メモリブロック。
 * @param[in]	_uSize		: 確保するサイズ。
 * @param[in]	_psFile		: 呼び出し元のファイル名。
 * @param[in]	_uLine		: 呼び出し元行数。
 * @param[in]	_eMode		: アロケートモード。
 * @return					: 確保したメモリへのポインタ。
 */
void* CMemAllocator::AllocFromMemBlock( CMemBlock* _pcMemBlock, USize _uSize, const S8* _psFile, U32 _uLine, EnAllocMode _eMode )
{
	#if defined( USE_MEMORY_DEBUG )
	MEM_ASSERT( _pcMemBlock );
	if (nullptr == _pcMemBlock)
	{
		return nullptr;
	}
	#endif // #if defined( USE_MEMORY_DEBUG )

	RemoveFreeList( _pcMemBlock );

	const USize uBlockSize = GetBlockSize( _uSize );
	const USize uOldBlockSize = _pcMemBlock->GetBlockSize();
	const USize uFreeBlockSize = uOldBlockSize - uBlockSize;

	// 残りのメモリでブロックを作成出来ない場合は新規に確保するメモリブロックの中に含める。
	const USize uMinBlockSize = GetBlockSize( 0 );
	const bool bExistFree = uMinBlockSize < uFreeBlockSize;
	USize uNewBlockSize = uBlockSize;
	if (!bExistFree)
	{
		uNewBlockSize = uOldBlockSize;
	}

	// 新規に確保。
	CMemBlock* pNewMemBlock = nullptr;
	CMemBlock* pNewFreeMemBlock = nullptr;

	switch (_eMode)
	{ 
	case EnAllocMode::enForward:
		pNewMemBlock = new(_pcMemBlock)CMemBlock( uNewBlockSize, _psFile, _uLine );
		if (bExistFree)
		{
			pNewFreeMemBlock = new( pNewMemBlock->GetNextBlock() )CMemBlock( uFreeBlockSize );
		}
		break;

	case EnAllocMode::enBack:
		if (bExistFree)
		{
			pNewFreeMemBlock = new(_pcMemBlock)CMemBlock( uFreeBlockSize );
			pNewMemBlock = new( _pcMemBlock->GetNextBlock() )CMemBlock( uNewBlockSize, _psFile, _uLine);
		}
		else
		{
			pNewMemBlock = new(_pcMemBlock)CMemBlock( uNewBlockSize, _psFile, _uLine );
		}
		break;

	default:
		ASSERT( !"Invailed case." );
		break;
	}

	void* pRet = nullptr;
	if (pNewMemBlock)
	{
		pNewMemBlock->SetUsed( true );
		pRet = pNewMemBlock->GetData();
	}
				
	// 残りの領域があれば、Freeリストに追加。
	if (pNewFreeMemBlock)
	{
		SetFreeList( pNewFreeMemBlock );
	}

#if defined( USE_MEMORY_DEBUG )
	UpdateDebugInfoByAlloc( pNewMemBlock->GetBlockSize() );
#endif // #if defined( USE_MEMORY_DEBUG )

	return pRet;
}

/**
 * brief	メモリを解放。
 */
void CMemAllocator::Free( void* _p )
{
	CCriticalSectionBlock cCSBlock ( &m_cCriticalSection );

#if defined( USE_MEMORY_FAILSAFE )
	MEM_ASSERT( _p );
	if (nullptr == _p)
	{
		return; // failsafe
	}
#endif // #if defined( USE_MEMORY_FAILSAFE )

	CMemBlock* pcMemBlock = reinterpret_cast<CMemBlock*>( static_cast<U8*>(_p) - sizeof( CMemBlock::StMemBlockHeader ) );
	MEM_ASSERT( pcMemBlock->IsUsed() );

#if defined( USE_MEMORY_DEBUG)
	MEM_ASSERT( false == pcMemBlock->IsErrorBufferOverRun() );
	UpdateDebugInfoByFree( pcMemBlock->GetBlockSize() );
#endif // #if defined( USE_MEMORY_DEBUG)

	pcMemBlock->SetUsed( false );

	// メモリブロックのマージ。
	CMemBlock* pcPrevMemBlock = pcMemBlock->GetPrevBlock();
#if defined( USE_MEMORY_FAILSAFE )
	MEM_ASSERT( pcPrevMemBlock );
	if (nullptr == pcPrevMemBlock)
	{
		return;	// failsafe
	}
#endif // #if defined( USE_MEMORY_FAILSAFE )

	CMemBlock* pcNextMemBlock = pcMemBlock->GetNextBlock();
#if defined( USE_MEMORY_FAILSAFE )
	MEM_ASSERT( pcNextMemBlock );
	if (nullptr == pcNextMemBlock)
	{
		return;
	}
#endif // #if defined( USE_MEMORY_FAILSAFE )

	USize uFreeBlockSize = pcMemBlock->GetBlockSize();
	CMemBlock* pcFreeMemBlockPointer = pcMemBlock;
	if (false == pcPrevMemBlock->IsUsed())
	{
		RemoveFreeList( pcPrevMemBlock );

		uFreeBlockSize += pcPrevMemBlock->GetBlockSize();
		pcFreeMemBlockPointer = pcPrevMemBlock;
	}
	if (false == pcNextMemBlock->IsUsed())
	{
		RemoveFreeList( pcNextMemBlock );
		
		uFreeBlockSize += pcNextMemBlock->GetBlockSize();
	}

	CMemBlock* pcFreeMemBlock = new(pcFreeMemBlockPointer)CMemBlock( uFreeBlockSize );
	SetFreeList( pcFreeMemBlock );
}

/**
 * @brief		このメモリアロケータで確保したポインタか。
 * @param[in]	_p	: チェックするポインタ。
 * @retval
 */
bool CMemAllocator::IsAllocatedPointer( void* _p ) const
{
	bool bRet = false;
	if (m_pMemory <= _p &&
		_p < m_pEndBlock)
	{
		bRet = true;
	}

	return bRet;
}

/**
 * @brief		サイズからレベルを取得。
 * @param[out]	_puOutFirst		:	FLI格納先。
 * @param[out]	_puOutSecond	:	SLI格納先。
 * @param[in]	_uBlockSize		:	ブロックサイズ。
 */
void CMemAllocator::GetLevel( U32* _puOutFirst, U32* _puOutSecond, USize _uBlockSize )
{
#if defined( USE_MEMORY_FAILSAFE )
	MEM_ASSERT( _puOutFirst );
	if (nullptr == _puOutFirst)
	{
		return;	// failsafe
	}

	MEM_ASSERT( _puOutSecond );
	if (nullptr == _puOutSecond)
	{
		return; // failsafe
	}
#endif //#if defined( USE_MEMORY_FAILSAFE )

	U32 uMaxBitIndex = 0;
	nBit::GetMaxBit( &uMaxBitIndex, _uBlockSize );

	if (uMaxBitIndex < s_cast<U32>(m_stInitParam.m_ePartition))
	{
		uMaxBitIndex = m_stInitParam.m_ePartition;
	}

	// 最上位ビットを折るマスク。
	const USize uMaskResetMaxBit = ( 1 << uMaxBitIndex ) - 1;	// ex 1000 0000 -> 0111 1111

	// シフト回数を求める。
	const U32 uShift = uMaxBitIndex - m_stInitParam.m_ePartition;

	*_puOutFirst = uMaxBitIndex;
	*_puOutSecond = s_cast<U32>( ( _uBlockSize & uMaskResetMaxBit ) >> uShift );

}

/**
 * @brief		Freeリストに領域をセット。
 * @param[in]	_pcMemBlock	: セットするブロック。
 */
void CMemAllocator::SetFreeList( CMemBlock* _pcMemBlock )
{
#if defined( USE_MEMORY_FAILSAFE )
	MEM_ASSERT( _pcMemBlock );
	if (nullptr == _pcMemBlock)
	{
		return; // failsafe
	}

	MEM_ASSERT( m_pFreeBlockArray );
	if (nullptr == m_pFreeBlockArray)
	{
		return; // failsafe
	}
#endif // #if defined( USE_MEMORY_FAILSAFE )

	const USize uBlockSize = _pcMemBlock->GetBlockSize();
	MEM_ASSERT( 0 < uBlockSize );
	U32 uFirstLevel = 0;
	U32 uSecondLevel = 0;
	GetLevel( &uFirstLevel, &uSecondLevel, uBlockSize );
	const U32 uIndex = GetFreeListIndex( uFirstLevel, uSecondLevel );

	if (nullptr != m_pFreeBlockArray[ uIndex ])
	{
		m_pFreeBlockArray[ uIndex ]->SetPrevList( _pcMemBlock );
		_pcMemBlock->SetNextList( m_pFreeBlockArray[ uIndex ] );
		m_pFreeBlockArray[ uIndex ] = _pcMemBlock;
	}
	else
	{
		m_pFreeBlockArray[ uIndex ] = _pcMemBlock;
		m_uIsFree |= s_cast<U64>(1) << uFirstLevel;
		m_uIsFreeArray[ uFirstLevel ] |= 1 << uSecondLevel;
	}
}

/**
 * @brief		Freeリストから領域を解除。
 * @param[in]	_pcMemBlock	: 解除するブロック。
 */
void CMemAllocator::RemoveFreeList( CMemBlock* _pcMemBlock )
{
#if defined( USE_MEMORY_FAILSAFE )
	MEM_ASSERT( _pcMemBlock );
	if (nullptr == _pcMemBlock)
	{
		return; // failsafe
	}

	MEM_ASSERT( m_pFreeBlockArray );
	if (nullptr == m_pFreeBlockArray)
	{
		return; // failsafe
	}
#endif // #if defined( USE_MEMORY_FAILSAFE )

	const USize uBlockSize = _pcMemBlock->GetBlockSize();
	MEM_ASSERT( 0 < uBlockSize );

	U32 uFirstLevel = 0;
	U32 uSecondLevel = 0;
	GetLevel( &uFirstLevel, &uSecondLevel, uBlockSize );
	const U32 uIndex = GetFreeListIndex( uFirstLevel, uSecondLevel );

	MEM_ASSERT( m_pFreeBlockArray[ uIndex ] );

	if (m_pFreeBlockArray[ uIndex ] == _pcMemBlock)
	{
		m_pFreeBlockArray[ uIndex ] = _pcMemBlock->GetNextList();
	}
	else
	{
		CMemBlock* pcPrevList = _pcMemBlock->GetPrevList();
		if (pcPrevList)
		{
			pcPrevList->SetNextList( _pcMemBlock->GetNextList() );
		}
		
		CMemBlock* pcNextList = _pcMemBlock->GetNextList();
		if (pcNextList)
		{
			pcNextList->SetPrevList( _pcMemBlock->GetPrevList() );
		}
	}

	if (nullptr == m_pFreeBlockArray[ uIndex ])
	{
		m_uIsFreeArray[ uFirstLevel ] &= ~( 1 << uSecondLevel );
		if (m_uIsFreeArray[ uFirstLevel ] == 0)
		{
			m_uIsFree &= ~( 1 << uFirstLevel );
		}
	}
}

/**
 * @brief		Freeリストから確保出来る領域のレベルを探す。
 * @param[out]	_pOutFirstLevel		: 1stLevelの格納先。
 * @param[out]	_pOutSecondLevel	: 2ndLevelの格納先。
 * @param[in]	_uBlockSize			: ブロックサイズ。
 */
bool CMemAllocator::SearchFreeListLevel( U32* _pOutFirstLevel, U32* _pOutSecondLevel, USize _uBlockSize )
{
#if defined( USE_MEMORY_FAILSAFE )
	MEM_ASSERT( _pOutFirstLevel );
	if (nullptr == _pOutFirstLevel)
	{
		return false;	// failsafe
	}

	MEM_ASSERT( _pOutSecondLevel );
	if (nullptr == _pOutSecondLevel)
	{
		return false;
	}
#endif // #if defined( USE_MEMORY_FAILSAFE )

	bool bRet = false;

	U32 uFirstLevel = 0;
	U32 uSecondLevel = 0;
	GetLevel( &uFirstLevel, &uSecondLevel, _uBlockSize );

	// 同じ1stLevelにフリーリストがあるか。
	const U32 uNextSecondLevel = uSecondLevel + 1;
	const U32 uMask = 
		( sc_uPartitionNumArray[m_stInitParam.m_ePartition] == uNextSecondLevel ) ? 0 :  0xFFFFFFFF << ( uNextSecondLevel );
	const U32 uIsFreeMasked = m_uIsFreeArray[ uFirstLevel ] & uMask;
	if (uIsFreeMasked != 0)
	{
		bRet = true;
		*_pOutFirstLevel = uFirstLevel;
		nBit::GetMinBit( _pOutSecondLevel, uIsFreeMasked );
	}
	else
	{
		const U64 uMask = 0xffffffffffffffff << ( uFirstLevel + 1 );
		const U64 uIsFreeMasked = m_uIsFree & uMask;
		if (uIsFreeMasked != 0)
		{
			bRet = true;
			nBit::GetMinBit( _pOutFirstLevel, uIsFreeMasked );
			nBit::GetMinBit( _pOutSecondLevel, m_uIsFreeArray[ *_pOutFirstLevel ] );
		}
	}

	return bRet;
}

/**
 * @brief		レベルからFreeリストのインデックスを取得。
 * @param[in]	_uFirstLevel
 * @param[in]	_uSecondLevel
 * @retval		インデックス値
 */
U32 CMemAllocator::GetFreeListIndex( U32 _uFirstLevel, U32 _uSecondLevel )
{ 
	return _uFirstLevel * sc_uPartitionNumArray[ m_stInitParam.m_ePartition ] + _uSecondLevel; 
}

#if defined( USE_MEMORY_DEBUG )

/**
 * @brief		全てのメモリブロック情報を出力。
 * @param[in]	_bPrintUsed	: 使用中のメモリブロックを表示するか。
 * @param[in]	_bPrintUsed	: 解放されたのメモリブロックを表示するか。
 */
void CMemAllocator::PrintDebugMemBlockInfoAll( bool _bPrintUsed, bool _bPrintFree )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	MEM_ASSERT( m_pMemory );
	if (nullptr == m_pMemory)
	{
		return; // failsafe
	}

	MEM_ASSERT( m_pEndBlock );
	if (nullptr == m_pEndBlock)
	{
		return; // failsafe
	}

	CMemBlock* pcMemBlock = r_cast<CMemBlock*>( m_pMemory );
	// 先頭のメモリブロックはフリーリストなので次のメモリブロックに移動。
	pcMemBlock = pcMemBlock->GetNextBlock();

	while (m_pEndBlock != pcMemBlock)
	{
		if (nullptr == pcMemBlock)
		{
			break; // failsafe
		}

		bool bPrint = false;
		if (pcMemBlock->IsUsed())
		{
			if (_bPrintUsed)
			{
				bPrint = true;
			}
		}
		else
		{
			if (_bPrintFree)
			{
				bPrint = true;
			}
		}

		if (bPrint)
		{
			PrintDebugMemBlockInfo( pcMemBlock );
		}

		pcMemBlock = pcMemBlock->GetNextBlock();
	}
}

/**
 * @brief		メモリデバッグ情報の取得。
 * @param[in]	_uTotalSize	: 合計メモリ。
 * @param[in]	_uUsedSize	: 既に使用済みのメモリ( CMemAllocatorで使用するサイズ)。
 */
void CMemAllocator::InitDebugInfo( USize _uTotalSize, USize _uUsedSize )
{
	m_stDebugMemoryInfo.Init();
	m_stDebugMemoryInfo.m_uMemorySizeTotal = _uTotalSize - _uUsedSize;
}

/**
 * @brief		Alloc()時のデバッグ情報の更新。
 * @param[in]	_uAllocBlockSize : 確保したメモリのサイズ。
 */
void CMemAllocator::UpdateDebugInfoByAlloc( USize _uAllocBlockSize )
{
	m_stDebugMemoryInfo.m_uMemorySizeUsed += _uAllocBlockSize;
	if (m_stDebugMemoryInfo.m_uMemorySizePeek < m_stDebugMemoryInfo.m_uMemorySizeUsed)
	{
		m_stDebugMemoryInfo.m_uMemorySizePeek = m_stDebugMemoryInfo.m_uMemorySizeUsed;
	}
	++m_stDebugMemoryInfo.m_uCountAlloc;
}

/**
 * @brief		Free()時のデバッグ情報の更新。
 * @param[in]	_uFreeBlockSize	: 開放したメモリのサイズ。
 */
void CMemAllocator::UpdateDebugInfoByFree( USize _uFreeBlockSize )
{
	m_stDebugMemoryInfo.m_uMemorySizeUsed -= _uFreeBlockSize;
	++m_stDebugMemoryInfo.m_uCountFree;
}

/**
 * @brief		メモリブロック情報を出力。
 * @param[in]	_pcMemBlock	: メモリブロック。
 */
void CMemAllocator::PrintDebugMemBlockInfo( CMemBlock* _pcMemBlock )
{
	MEM_ASSERT( _pcMemBlock );
	if (nullptr == _pcMemBlock)
	{
		return; // failsafe
	}

	CMemBlock::StMemBlockHeader* pstHeader = _pcMemBlock->GetHeader();
	MEM_ASSERT( pstHeader );
	if (nullptr == pstHeader)
	{
		return;	// failsafe
	}

	const USize uBlockSize = _pcMemBlock->GetBlockSize();

	Log( _T( "-------- MemBlock[%p] --------" ), _pcMemBlock );
	Log( _T( "BlockSize   : %lld[byte]" ), uBlockSize );
	Log( _T( "AllocSize   : %lld[byte]" ), pstHeader->m_uAllocSize );
	if (nullptr != pstHeader->m_psDebugAllocFile)
	{
		Log( _T( "File        : %s[%d]" ), pstHeader->m_psDebugAllocFile, pstHeader->m_uDebugAllocLine );
	}
	Log( _T( "Status      : %s" ), ( _pcMemBlock->IsUsed() ) ? _T( "Used" ) : _T( "Free" ) );
}

#endif // #if defined( USE_MEMORY_DEBUG )
