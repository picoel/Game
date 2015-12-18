/**
  * @file	Worker.cpp
  * @brief	同期ワーカースレッド。
  * @date 2015/08/28 02:01:58
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Worker/Worker.h"
#include "Lib/Worker/WorkerManager.h"
#include "Lib/Worker/Job.h"

/**
 * @brief	コンストラクタ。
 */
CWorker::CWorker()
	: CSingleton<CWorker>()
	, m_pcWorkerManagerSync( nullptr )
	, m_pcWorkerManagerUnSync( nullptr )
{
}

/**
 * @brief	デストラクタ。
 */
CWorker::~CWorker()
{
	P_DELETE( m_pcWorkerManagerSync );
	P_DELETE( m_pcWorkerManagerUnSync );
}

/**
 * @brief	初期化。
 * @param	_rstInit	: 初期化用パラメータ。
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
 * @brief	リクエスト。
 * @param	_pcJob	: ワーカースレッドで行う仕事。
 * @param	_bSync	: 同期して実行するか。
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
 * @brief	同期。
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

	// 全ての仕事が完了するまで待機。
	while (false == pcThis->m_pcWorkerManagerSync->IsWaitAll());
}
