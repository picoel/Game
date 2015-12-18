/**
  * @file	WorkerChannel.cpp
  * @brief	WorkerThread�ɂ�����Channel�B
  * @date 2015/08/08 02:55:10
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Worker/WorkerChannel.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CWorkerChannel::CWorkerChannel()
	: m_cQueueJob()
	, m_cCriticalSection()
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CWorkerChannel::~CWorkerChannel()
{
}

/**
 * @brief	�d����ǉ��B
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
 * @brief	�d�����擾�B
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
