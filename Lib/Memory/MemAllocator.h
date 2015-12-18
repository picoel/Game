/**
  * @file	MemAllocator.h
  * @brief	�������A���P�[�^�[
  * @date	2015/04/18 11:52:10
  */

#ifndef INCLUDE_MEMALLOCATOR_H
#define INCLUDE_MEMALLOCATOR_H

#include "Lib/Thread/CriticalSection.h"
#include "Lib/Memory/MemBlock.h"

/*
 *	@class	CMemAllocator
 */
class CMemAllocator
{
public:
	/// �������p�p�����[�^�B
	struct StInitParam
	{
		enum EnPartitionNum
		{
			enPartitionNum_1 = 0,
			enPartitionNum_2,
			enPartitionNum_4,
			enPartitionNum_8,
			enPartitionNum_16,
			enPartitionNum_32,

			enPartitionNum_Max,
		};

		USize			m_uSize;		///< �m�ۂ��郁�����T�C�Y�B
		EnPartitionNum	m_ePartition;	///< �������������B

		void Init()
		{
			m_uSize = 0;
			m_ePartition = enPartitionNum_32;
		}
	};

	/// �A���P�[�g���[�h�B
	enum class EnAllocMode : U32
	{
		enForward,
		enBack,
	};

public:
	/// �R���X�g���N�^�B
	CMemAllocator( const StInitParam& _rstInitParam );

	/// �f�X�g���N�^�B
	virtual ~CMemAllocator();

	/// ���������m�ہB
	void* Alloc( USize _uSize, const S8* _psFile, U32 _uLine );
	/// �Ō�����烁�������m�ہB
	void* AllocBack( USize _uSize, const S8* _psFile, U32 _uLine );
	/// �w�肵���������u���b�N���烁�������m�ہB
	void* AllocFromMemBlock( CMemBlock* _pcMemBlock, USize _uSize, const S8* _psFile, U32 _uLine, EnAllocMode _eMode );

	/// ������������B
	void Free( void* _p );

	/// ���̃������A���P�[�^�Ŋm�ۂ����|�C���^���B
	bool IsAllocatedPointer( void* _p ) const;

	static void* operator new( std::size_t _uSize )
	{
		return malloc( _uSize );
	}

	static void operator delete( void* _p )
	{
		free( _p );
	}

private:
	/// FirstLevel�B
	enum EnFirstLevel
	{
		enFirstLevel_Max = sizeof( USize ) * 8,
	};

private:
	/// �v�����ꂽ�T�C�Y����A���ۂɊm�ۂ���u���b�N�T�C�Y���擾�B
	USize GetBlockSize(USize _uSize)
	{ 
		return sizeof( CMemBlock::StMemBlockHeader ) + _uSize + sizeof( CMemBlock::StMemBlockFooter );
	}

	/// �T�C�Y���烌�x�����擾�B
	void GetLevel( U32* _puOutFirst, U32* _puOutSecond, USize _uBlockSize );

	/// Free���X�g�ɗ̈���Z�b�g�B
	void SetFreeList( CMemBlock* _pcMemBlock );
	/// Free���X�g����̈�������B
	void RemoveFreeList( CMemBlock* _pcMemBlock );
	/// Free���X�g����m�ۏo����̈�̃��x����T���B
	bool SearchFreeListLevel( U32* _pOutFirstLevel, U32* _pOutSecondLevel, USize _uBlockSize );
	/// ���x������Free���X�g�̃C���f�b�N�X���擾�B
	U32 GetFreeListIndex( U32 _uFirstLevel, U32 _uSecondLevel );

private:
	StInitParam	m_stInitParam;

	U8*			m_pMemory;								///< �m�ۂ����������B
	CMemBlock*	m_pEndBlock;							///< �I�[�u���b�N�B
	CMemBlock**	m_pFreeBlockArray;						///< ����ς݂̗̈惊�X�g�B
	U64			m_uIsFree;								///< ����ς݂̗̈悪���邩�B(1stLevel)
	U32			m_uIsFreeArray[ enFirstLevel_Max ];		///< ����ς݂̗̈悪���邩�B(2ndLevel)

	CCriticalSection	m_cCriticalSection;				///< �N���e�B�J���Z�N�V�����B

#if defined( USE_MEMORY_DEBUG )
public:
	/// �������̃f�o�b�O���\���́B
	struct StDebugMemoryInfo
	{
		USize		m_uMemorySizeTotal;			///< ���v�������T�C�Y�B
		USize		m_uMemorySizeUsed;			///< �g�p�������T�C�Y�B
		USize		m_uMemorySizePeek;			///< �s�[�N���̎g�p�������T�C�Y�B
		U32			m_uCountAlloc;				///< Alloc()���Ă΂ꂽ�񐔁B
		U32			m_uCountFree;				///< Free()���Ă΂ꂽ�񐔁B

		void Init()
		{
			m_uMemorySizeTotal = 0;
			m_uMemorySizeUsed = 0;
			m_uMemorySizePeek = 0;
			m_uCountAlloc = 0;
			m_uCountFree = 0;
		}
	};

	/// �������f�o�b�O���̎擾�B
	const StDebugMemoryInfo& GetDebugMemoryInfo() const{ return m_stDebugMemoryInfo; }

	/// �S�Ẵ������u���b�N�����o�́B
	void PrintDebugMemBlockInfoAll( bool _bPrintUsed, bool _bPrintFree );

private:
	/// �������f�o�b�O���̏������B
	void InitDebugInfo( USize _uTotalSize, USize _uUsedSize );
	/// Alloc()���̃f�o�b�O���̍X�V�B
	void UpdateDebugInfoByAlloc( USize _uAllocBlockSize );
	/// Free()���̃f�o�b�O���̍X�V�B
	void UpdateDebugInfoByFree( USize _uFreeBlockSize );

	/// �������u���b�N�����o�́B
	void PrintDebugMemBlockInfo( CMemBlock* _pcMemBlock );

	StDebugMemoryInfo	m_stDebugMemoryInfo;
	
#endif // #if defined( USE_MEMORY_DEBUG )
};

#endif // #ifndef INCLUDE_MEMALLOCATOR_H
