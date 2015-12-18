/**
  * @file	MemDefinition.cpp
  * @brief	メモリ関連の定義。
  * @date 2015/05/24 03:54:05
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Memory/MemDefinition.h"
#include "Lib/Memory/MemManager.h"

/**
 * @brief		メモリ確保。
 * @param[in]	_uSize		: 確保するサイズ。
 * @param[in]	_ePage		: アロケートページ。
 * @param[in]	_eMode		: アロケートモード。
 * @param[in]	_psFile		: 呼び出し元ファイル。
 * @param[in]	_uLine		: 呼び出し元行数。
 * @retval		void*		: 確保したメモリへのポインタ。
 */
void* nMem::Alloc( USize _uSize, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode, const S8* _psFile, U32 _uLine )
{
	CMemManager* pcMemManager = CMemManager::GetInstance();
	if (pcMemManager)
	{
		return pcMemManager->Alloc( _uSize, _ePage, _eMode, _psFile, _uLine );
	}
	else
	{
		return malloc( _uSize );
	}
}

/**
 * @brief		メモリ解放。
 * @param[in]	_p			: 解放するポインタ。
 */
void nMem::Free( void* _p )
{
	CMemManager* pcMemManager = CMemManager::GetInstance();
	if (pcMemManager)
	{
		return pcMemManager->Free( _p );
	}
	else
	{
		return free( _p );
	}
}
