/**
  * @file	MemBlock.h
  * @brief	メモリブロッククラスの定義。
  * @date 2015/05/02 00:16:52
  */

#ifndef INCLUDE_CMEMBLOCK_H
#define INCLUDE_CMEMBLOCK_H

/*
 * @class CMemBlock
 * @brief メモリブロック。
 */
class CMemBlock
{
public:
	struct StMemBlockHeader
	{
		enum EnFlag
		{
			enFlag_Free,
			enFlag_Used,
		};

		USize	m_uAllocSize;
		S32	m_sFlag;
		CMemBlock*	m_pPrev;
		CMemBlock*	m_pNext;

#if defined( USE_MEMORY_DEBUG )
		const S8*	m_psDebugAllocFile;
		U32			m_uDebugAllocLine;
#endif // #if defined( USE_MEMORY_DEBUG ) 

		void Init()
		{
			m_uAllocSize = 0;
			m_sFlag = enFlag_Free;
			m_pPrev = nullptr;
			m_pNext = nullptr;
#if defined( USE_MEMORY_DEBUG )
			m_psDebugAllocFile = nullptr;
			m_uDebugAllocLine = 0;
#endif // #if defined( USE_MEMORY_DEBUG )
		}
	};

	struct StMemBlockFooter
	{
		USize m_uBlockSize;

#if defined( USE_MEMORY_DEBUG )
		U32 m_uOverRunCheck;	///< バッファオーバーランチェック用。
#endif // #if defined( USE_MEMORY_DEBUG)
		void Init()
		{
			m_uBlockSize = 0;
#if defined( USE_MEMORY_DEBUG )
			m_uOverRunCheck = 0xDEADC0DE;
#endif // #if defined( USE_MEMORY_DEBUG)
		}
	};

public:
	/// コンストラクタ。
	CMemBlock( USize _uBlockSize );
	CMemBlock( USize _uBlockSize, const S8* _psFile, U32 _uLine );

	/// デストラクタ。
	~CMemBlock(){};

	/// 初期化。
	void Init( USize _uBlockSize, const S8* _psFile, U32 _uLine );

	/// ヘッダーを取得。
	inline StMemBlockHeader* GetHeader(){ return &m_stMemBlockHeader; }
	/// データを取得。
	inline void*	GetData() { return r_cast<U8*>(this) + sizeof( StMemBlockHeader ); }
	/// フッターを取得。
	inline StMemBlockFooter* GetFooter()
	{ 
		void* pRet = r_cast<U8*>( this ) + sizeof( StMemBlockHeader ) + m_stMemBlockHeader.m_uAllocSize;
		return s_cast<StMemBlockFooter*>( pRet ); 
	}

	/// ブロックのサイズを取得。
	inline USize GetBlockSize(){ return GetFooter()->m_uBlockSize; }

	/// 使用中かどうかを設定。
	inline void SetUsed( bool _bUsed ){ m_stMemBlockHeader.m_sFlag = _bUsed ? StMemBlockHeader::enFlag_Used : StMemBlockHeader::enFlag_Free; }
	/// 使用中かどうか。
	inline bool IsUsed() const{ return m_stMemBlockHeader.m_sFlag == StMemBlockHeader::enFlag_Used; }

	/// 前のブロックを取得。
	inline CMemBlock* GetPrevBlock()
	{
		U8* const pThis = r_cast<U8*>( this );
		StMemBlockFooter* pPrevFooter = r_cast<StMemBlockFooter*>( pThis - sizeof( StMemBlockFooter ) );
		return r_cast<CMemBlock*>( pThis - pPrevFooter->m_uBlockSize );
	}
	/// 次のブロックを取得。
	inline CMemBlock* GetNextBlock(){ return r_cast<CMemBlock*>( r_cast<U8*>( this ) + GetBlockSize() ); }

	/// 次のリストを設定。
	inline void SetNextList( CMemBlock* _pcMemBlock ){ m_stMemBlockHeader.m_pNext = _pcMemBlock;}
	/// 次のリストを取得。
	inline CMemBlock* GetNextList(){ return m_stMemBlockHeader.m_pNext;}
	/// 前のリストを設定。
	inline void SetPrevList(CMemBlock* _pcMemBlock ){ m_stMemBlockHeader.m_pPrev = _pcMemBlock;}
	/// 前のリストを取得。
	inline CMemBlock* GetPrevList(){ return m_stMemBlockHeader.m_pPrev; }

#if defined( USE_MEMORY_DEBUG)
	/// バッファオーバーランチェック。
	bool IsErrorBufferOverRun(){ return 0xDEADC0DE != GetFooter()->m_uOverRunCheck; }
#endif // #if defined( USE_MEMORY_DEBUG)
private:
	StMemBlockHeader	m_stMemBlockHeader;
};

#endif // #ifndef INCLUDE_CMEMBLOCK_H