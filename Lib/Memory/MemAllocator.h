/**
  * @file	MemAllocator.h
  * @brief	メモリアロケーター
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
	/// 初期化用パラメータ。
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

		USize			m_uSize;		///< 確保するメモリサイズ。
		EnPartitionNum	m_ePartition;	///< メモリ分割数。

		void Init()
		{
			m_uSize = 0;
			m_ePartition = enPartitionNum_32;
		}
	};

	/// アロケートモード。
	enum class EnAllocMode : U32
	{
		enForward,
		enBack,
	};

public:
	/// コンストラクタ。
	CMemAllocator( const StInitParam& _rstInitParam );

	/// デストラクタ。
	virtual ~CMemAllocator();

	/// メモリを確保。
	void* Alloc( USize _uSize, const S8* _psFile, U32 _uLine );
	/// 最後尾からメモリを確保。
	void* AllocBack( USize _uSize, const S8* _psFile, U32 _uLine );
	/// 指定したメモリブロックからメモリを確保。
	void* AllocFromMemBlock( CMemBlock* _pcMemBlock, USize _uSize, const S8* _psFile, U32 _uLine, EnAllocMode _eMode );

	/// メモリを解放。
	void Free( void* _p );

	/// このメモリアロケータで確保したポインタか。
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
	/// FirstLevel。
	enum EnFirstLevel
	{
		enFirstLevel_Max = sizeof( USize ) * 8,
	};

private:
	/// 要求されたサイズから、実際に確保するブロックサイズを取得。
	USize GetBlockSize(USize _uSize)
	{ 
		return sizeof( CMemBlock::StMemBlockHeader ) + _uSize + sizeof( CMemBlock::StMemBlockFooter );
	}

	/// サイズからレベルを取得。
	void GetLevel( U32* _puOutFirst, U32* _puOutSecond, USize _uBlockSize );

	/// Freeリストに領域をセット。
	void SetFreeList( CMemBlock* _pcMemBlock );
	/// Freeリストから領域を解除。
	void RemoveFreeList( CMemBlock* _pcMemBlock );
	/// Freeリストから確保出来る領域のレベルを探す。
	bool SearchFreeListLevel( U32* _pOutFirstLevel, U32* _pOutSecondLevel, USize _uBlockSize );
	/// レベルからFreeリストのインデックスを取得。
	U32 GetFreeListIndex( U32 _uFirstLevel, U32 _uSecondLevel );

private:
	StInitParam	m_stInitParam;

	U8*			m_pMemory;								///< 確保したメモリ。
	CMemBlock*	m_pEndBlock;							///< 終端ブロック。
	CMemBlock**	m_pFreeBlockArray;						///< 解放済みの領域リスト。
	U64			m_uIsFree;								///< 解放済みの領域があるか。(1stLevel)
	U32			m_uIsFreeArray[ enFirstLevel_Max ];		///< 解放済みの領域があるか。(2ndLevel)

	CCriticalSection	m_cCriticalSection;				///< クリティカルセクション。

#if defined( USE_MEMORY_DEBUG )
public:
	/// メモリのデバッグ情報構造体。
	struct StDebugMemoryInfo
	{
		USize		m_uMemorySizeTotal;			///< 合計メモリサイズ。
		USize		m_uMemorySizeUsed;			///< 使用メモリサイズ。
		USize		m_uMemorySizePeek;			///< ピーク時の使用メモリサイズ。
		U32			m_uCountAlloc;				///< Alloc()が呼ばれた回数。
		U32			m_uCountFree;				///< Free()が呼ばれた回数。

		void Init()
		{
			m_uMemorySizeTotal = 0;
			m_uMemorySizeUsed = 0;
			m_uMemorySizePeek = 0;
			m_uCountAlloc = 0;
			m_uCountFree = 0;
		}
	};

	/// メモリデバッグ情報の取得。
	const StDebugMemoryInfo& GetDebugMemoryInfo() const{ return m_stDebugMemoryInfo; }

	/// 全てのメモリブロック情報を出力。
	void PrintDebugMemBlockInfoAll( bool _bPrintUsed, bool _bPrintFree );

private:
	/// メモリデバッグ情報の初期化。
	void InitDebugInfo( USize _uTotalSize, USize _uUsedSize );
	/// Alloc()時のデバッグ情報の更新。
	void UpdateDebugInfoByAlloc( USize _uAllocBlockSize );
	/// Free()時のデバッグ情報の更新。
	void UpdateDebugInfoByFree( USize _uFreeBlockSize );

	/// メモリブロック情報を出力。
	void PrintDebugMemBlockInfo( CMemBlock* _pcMemBlock );

	StDebugMemoryInfo	m_stDebugMemoryInfo;
	
#endif // #if defined( USE_MEMORY_DEBUG )
};

#endif // #ifndef INCLUDE_MEMALLOCATOR_H
