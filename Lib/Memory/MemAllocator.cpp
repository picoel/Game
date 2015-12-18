/**
  * @file	MemAllocator.cpp
  * @brief	�������A���P�[�^�[
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
 * @brief		�R���X�g���N�^�B
 * @param[in]	_rstInitParam	: �������p�p�����[�^
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

	// �m�ۂ����������̐擪�Ƀt���[���X�g���쐬�B
	const USize uFreeListSize = enFirstLevel_Max * sc_uPartitionNumArray[m_stInitParam.m_ePartition];
	const USize uFreeListBlockSize = GetBlockSize( sizeof( CMemBlock** ) * uFreeListSize );
	CMemBlock* pcFreeListMemBlock = new( m_pMemory ) CMemBlock( uFreeListBlockSize );
	pcFreeListMemBlock->SetUsed( true );
	m_pFreeBlockArray = s_cast<CMemBlock**>( pcFreeListMemBlock->GetData() );
	for (U32 ii = 0; ii < uFreeListSize; ++ii)
	{
		m_pFreeBlockArray[ ii ] = nullptr;
	}

	// �}�[�W�̍ۂɗ̈�𒴂��Ȃ��悤�ɁA�I�[�Ƀ_�~�[��u���B
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
 * @brief	�f�X�g���N�^�B
 */
CMemAllocator::~CMemAllocator()
{
	free( m_pMemory );
}

/**
 * @brief		���������m�ہB
 * @param[in]	_uSize	: �m�ۂ���T�C�Y�B
 * @param[in]	_psFile	: �Ăяo�����̃t�@�C�����B
 * @param[in]	_uLine	: �Ăяo�����s���B
 * @return				: �m�ۂ����������ւ̃|�C���^�B
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
 * @brief		�Ō�����烁�������m�ہB
 * @param[in]	_uSize	: �m�ۂ���T�C�Y�B
 * @param[in]	_psFile	: �Ăяo�����̃t�@�C�����B
 * @param[in]	_uLine	: �Ăяo�����s���B
 * @return				: �m�ۂ����������ւ̃|�C���^�B
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

	// ��납�烁�������m�ۏo���郁�����u���b�N��T���B
	CMemBlock* pcMemBlock = m_pEndBlock->GetPrevBlock();
	CMemBlock* pcFindMemBlock = nullptr;
	while (s_cast<void*>(m_pMemory) < s_cast<void*>(pcMemBlock))
	{
		if (pcMemBlock->IsUsed())
		{
			// �g�p���Ȃ�Ίm�ۏo���Ȃ��B
		}
		else if (pcMemBlock->GetBlockSize() < _uSize)
		{
			// �T�C�Y������Ȃ���Ύg�p�o���Ȃ��B
		}
		else
		{
			// �g�p�\�B
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
 * @brief	�w�肵���������u���b�N���烁�������m�ہB
 * @param[in]	_pcMemBlock	; �������u���b�N�B
 * @param[in]	_uSize		: �m�ۂ���T�C�Y�B
 * @param[in]	_psFile		: �Ăяo�����̃t�@�C�����B
 * @param[in]	_uLine		: �Ăяo�����s���B
 * @param[in]	_eMode		: �A���P�[�g���[�h�B
 * @return					: �m�ۂ����������ւ̃|�C���^�B
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

	// �c��̃������Ńu���b�N���쐬�o���Ȃ��ꍇ�͐V�K�Ɋm�ۂ��郁�����u���b�N�̒��Ɋ܂߂�B
	const USize uMinBlockSize = GetBlockSize( 0 );
	const bool bExistFree = uMinBlockSize < uFreeBlockSize;
	USize uNewBlockSize = uBlockSize;
	if (!bExistFree)
	{
		uNewBlockSize = uOldBlockSize;
	}

	// �V�K�Ɋm�ہB
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
				
	// �c��̗̈悪����΁AFree���X�g�ɒǉ��B
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
 * brief	������������B
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

	// �������u���b�N�̃}�[�W�B
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
 * @brief		���̃������A���P�[�^�Ŋm�ۂ����|�C���^���B
 * @param[in]	_p	: �`�F�b�N����|�C���^�B
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
 * @brief		�T�C�Y���烌�x�����擾�B
 * @param[out]	_puOutFirst		:	FLI�i�[��B
 * @param[out]	_puOutSecond	:	SLI�i�[��B
 * @param[in]	_uBlockSize		:	�u���b�N�T�C�Y�B
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

	// �ŏ�ʃr�b�g��܂�}�X�N�B
	const USize uMaskResetMaxBit = ( 1 << uMaxBitIndex ) - 1;	// ex 1000 0000 -> 0111 1111

	// �V�t�g�񐔂����߂�B
	const U32 uShift = uMaxBitIndex - m_stInitParam.m_ePartition;

	*_puOutFirst = uMaxBitIndex;
	*_puOutSecond = s_cast<U32>( ( _uBlockSize & uMaskResetMaxBit ) >> uShift );

}

/**
 * @brief		Free���X�g�ɗ̈���Z�b�g�B
 * @param[in]	_pcMemBlock	: �Z�b�g����u���b�N�B
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
 * @brief		Free���X�g����̈�������B
 * @param[in]	_pcMemBlock	: ��������u���b�N�B
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
 * @brief		Free���X�g����m�ۏo����̈�̃��x����T���B
 * @param[out]	_pOutFirstLevel		: 1stLevel�̊i�[��B
 * @param[out]	_pOutSecondLevel	: 2ndLevel�̊i�[��B
 * @param[in]	_uBlockSize			: �u���b�N�T�C�Y�B
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

	// ����1stLevel�Ƀt���[���X�g�����邩�B
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
 * @brief		���x������Free���X�g�̃C���f�b�N�X���擾�B
 * @param[in]	_uFirstLevel
 * @param[in]	_uSecondLevel
 * @retval		�C���f�b�N�X�l
 */
U32 CMemAllocator::GetFreeListIndex( U32 _uFirstLevel, U32 _uSecondLevel )
{ 
	return _uFirstLevel * sc_uPartitionNumArray[ m_stInitParam.m_ePartition ] + _uSecondLevel; 
}

#if defined( USE_MEMORY_DEBUG )

/**
 * @brief		�S�Ẵ������u���b�N�����o�́B
 * @param[in]	_bPrintUsed	: �g�p���̃������u���b�N��\�����邩�B
 * @param[in]	_bPrintUsed	: ������ꂽ�̃������u���b�N��\�����邩�B
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
	// �擪�̃������u���b�N�̓t���[���X�g�Ȃ̂Ŏ��̃������u���b�N�Ɉړ��B
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
 * @brief		�������f�o�b�O���̎擾�B
 * @param[in]	_uTotalSize	: ���v�������B
 * @param[in]	_uUsedSize	: ���Ɏg�p�ς݂̃�����( CMemAllocator�Ŏg�p����T�C�Y)�B
 */
void CMemAllocator::InitDebugInfo( USize _uTotalSize, USize _uUsedSize )
{
	m_stDebugMemoryInfo.Init();
	m_stDebugMemoryInfo.m_uMemorySizeTotal = _uTotalSize - _uUsedSize;
}

/**
 * @brief		Alloc()���̃f�o�b�O���̍X�V�B
 * @param[in]	_uAllocBlockSize : �m�ۂ����������̃T�C�Y�B
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
 * @brief		Free()���̃f�o�b�O���̍X�V�B
 * @param[in]	_uFreeBlockSize	: �J�������������̃T�C�Y�B
 */
void CMemAllocator::UpdateDebugInfoByFree( USize _uFreeBlockSize )
{
	m_stDebugMemoryInfo.m_uMemorySizeUsed -= _uFreeBlockSize;
	++m_stDebugMemoryInfo.m_uCountFree;
}

/**
 * @brief		�������u���b�N�����o�́B
 * @param[in]	_pcMemBlock	: �������u���b�N�B
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
