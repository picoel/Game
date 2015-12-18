/**
  * @file	MemDefinition.cpp
  * @brief	�������֘A�̒�`�B
  * @date 2015/05/24 03:54:05
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Memory/MemDefinition.h"
#include "Lib/Memory/MemManager.h"

/**
 * @brief		�������m�ہB
 * @param[in]	_uSize		: �m�ۂ���T�C�Y�B
 * @param[in]	_ePage		: �A���P�[�g�y�[�W�B
 * @param[in]	_eMode		: �A���P�[�g���[�h�B
 * @param[in]	_psFile		: �Ăяo�����t�@�C���B
 * @param[in]	_uLine		: �Ăяo�����s���B
 * @retval		void*		: �m�ۂ����������ւ̃|�C���^�B
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
 * @brief		����������B
 * @param[in]	_p			: �������|�C���^�B
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
