/**
  * @file	WorkerChannel.cpp
  * @brief	WorkerThreadにおけるChannel。
  * @date 2015/08/08 02:55:10
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Worker/WorkerChannel.h"

/**
 * @brief	コンストラクタ。
 */
CWorkerChannel::CWorkerChannel()
	: m_cQueueJob()
	, m_cCriticalSection()
{
}

/**
 * @brief	デストラクタ。
 */
CWorkerChannel::~CWorkerChannel()
{
}

/**
 * @brief	仕事を追加。
 */
void CWorkerChannel::PutJob( CJob* _pcJob )
{
	ASSERT( _pcJob );
	if (nullptr == _pcJob)
	{
		return;	// failsafe
	}

	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	m_cQueueJob.push( _pcJob );
}

/**
 * @brief	仕事を取得。
 */
CJob* CWorkerChannel::TakeJob()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	CJob* pcRet = nullptr;

	if (false == m_cQueueJob.empty())
	{
		pcRet = m_cQueueJob.front();
		m_cQueueJob.pop();
	}
	return pcRet;
}
