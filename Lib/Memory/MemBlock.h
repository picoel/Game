/**
  * @file	MemBlock.h
  * @brief	�������u���b�N�N���X�̒�`�B
  * @date 2015/05/02 00:16:52
  */

#ifndef INCLUDE_CMEMBLOCK_H
#define INCLUDE_CMEMBLOCK_H

/*
 * @class CMemBlock
 * @brief �������u���b�N�B
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
		U32 m_uOverRunCheck;	///< �o�b�t�@�I�[�o�[�����`�F�b�N�p�B
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
	/// �R���X�g���N�^�B
	CMemBlock( USize _uBlockSize );
	CMemBlock( USize _uBlockSize, const S8* _psFile, U32 _uLine );

	/// �f�X�g���N�^�B
	~CMemBlock(){};

	/// �������B
	void Init( USize _uBlockSize, const S8* _psFile, U32 _uLine );

	/// �w�b�_�[���擾�B
	inline StMemBlockHeader* GetHeader(){ return &m_stMemBlockHeader; }
	/// �f�[�^���擾�B
	inline void*	GetData() { return r_cast<U8*>(this) + sizeof( StMemBlockHeader ); }
	/// �t�b�^�[���擾�B
	inline StMemBlockFooter* GetFooter()
	{ 
		void* pRet = r_cast<U8*>( this ) + sizeof( StMemBlockHeader ) + m_stMemBlockHeader.m_uAllocSize;
		return s_cast<StMemBlockFooter*>( pRet ); 
	}

	/// �u���b�N�̃T�C�Y���擾�B
	inline USize GetBlockSize(){ return GetFooter()->m_uBlockSize; }

	/// �g�p�����ǂ�����ݒ�B
	inline void SetUsed( bool _bUsed ){ m_stMemBlockHeader.m_sFlag = _bUsed ? StMemBlockHeader::enFlag_Used : StMemBlockHeader::enFlag_Free; }
	/// �g�p�����ǂ����B
	inline bool IsUsed() const{ return m_stMemBlockHeader.m_sFlag == StMemBlockHeader::enFlag_Used; }

	/// �O�̃u���b�N���擾�B
	inline CMemBlock* GetPrevBlock()
	{
		U8* const pThis = r_cast<U8*>( this );
		StMemBlockFooter* pPrevFooter = r_cast<StMemBlockFooter*>( pThis - sizeof( StMemBlockFooter ) );
		return r_cast<CMemBlock*>( pThis - pPrevFooter->m_uBlockSize );
	}
	/// ���̃u���b�N���擾�B
	inline CMemBlock* GetNextBlock(){ return r_cast<CMemBlock*>( r_cast<U8*>( this ) + GetBlockSize() ); }

	/// ���̃��X�g��ݒ�B
	inline void SetNextList( CMemBlock* _pcMemBlock ){ m_stMemBlockHeader.m_pNext = _pcMemBlock;}
	/// ���̃��X�g���擾�B
	inline CMemBlock* GetNextList(){ return m_stMemBlockHeader.m_pNext;}
	/// �O�̃��X�g��ݒ�B
	inline void SetPrevList(CMemBlock* _pcMemBlock ){ m_stMemBlockHeader.m_pPrev = _pcMemBlock;}
	/// �O�̃��X�g���擾�B
	inline CMemBlock* GetPrevList(){ return m_stMemBlockHeader.m_pPrev; }

#if defined( USE_MEMORY_DEBUG)
	/// �o�b�t�@�I�[�o�[�����`�F�b�N�B
	bool IsErrorBufferOverRun(){ return 0xDEADC0DE != GetFooter()->m_uOverRunCheck; }
#endif // #if defined( USE_MEMORY_DEBUG)
private:
	StMemBlockHeader	m_stMemBlockHeader;
};

#endif // #ifndef INCLUDE_CMEMBLOCK_H