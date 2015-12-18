/**
  * @file	Worker.cpp
  * @brief	�������[�J�[�X���b�h�B
  * @date 2015/08/28 02:01:58
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Worker/Worker.h"
#include "Lib/Worker/WorkerManager.h"
#include "Lib/Worker/Job.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CWorker::CWorker()
	: CSingleton<CWorker>()
	, m_pcWorkerManagerSync( nullptr )
	, m_pcWorkerManagerUnSync( nullptr )
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CWorker::~CWorker()
{
	P_DELETE( m_pcWorkerManagerSync );
	P_DELETE( m_pcWorkerManagerUnSync );
}

/**
 * @brief	�������B
 * @param	_rstInit	: �������p�p�����[�^�B
 */
void CWorker::Init( const StInitParam& _rstInit )
{
	ASSERT( nullptr == m_pcWorkerManagerSync );
	P_DELETE( m_pcWorkerManagerSync );
	m_pcWorkerManagerSync = pnew CWorkerManager( _rstInit.m_uWorkerSyncNum );

	ASSERT( nullptr == m_pcWorkerManagerUnSync );
	P_DELETE( m_pcWorkerManagerUnSync );
	m_pcWorkerManagerUnSync = pnew CWorkerManager( _rstInit.m_uWorkerUnSyncNum );
}

/**
 * @brief	���N�G�X�g�B
 * @param	_pcJob	: ���[�J�[�X���b�h�ōs���d���B
 * @param	_bSync	: �������Ď��s���邩�B
 */
void CWorker::RequestJob( CJob* _pcJob, bool _bSync )
{
	CWorker* pcThis = GetInstance();
	ASSERT( pcThis );
	if (nullptr == pcThis)
	{
		return;	// failsafe
	}

	ASSERT( pcThis->m_pcWorkerManagerSync );
	if (nullptr == pcThis->m_pcWorkerManagerSync)
	{
		return;	// failsafe
	}

	ASSERT( pcThis->m_pcWorkerManagerUnSync );
	if (nullptr == pcThis->m_pcWorkerManagerUnSync)
	{
		return;	// failsafe
	}

	if (_bSync)
	{
		pcThis->m_pcWorkerManagerSync->RequestJob( _pcJob );
	}
	else
	{
		pcThis->m_pcWorkerManagerUnSync->RequestJob( _pcJob );
	}

}

/**
 * @brief	�����B
 */
void CWorker::Sync()
{
	CWorker* pcThis = GetInstance();
	ASSERT( pcThis );
	if (nullptr == pcThis)
	{
		return;	// failsafe
	}

	ASSERT( pcThis->m_pcWorkerManagerSync );
	if (nullptr == pcThis->m_pcWorkerManagerSync)
	{
		return;	// failsafe

	}

	// �S�Ă̎d������������܂őҋ@�B
	while (false == pcThis->m_pcWorkerManagerSync->IsWaitAll());
}
