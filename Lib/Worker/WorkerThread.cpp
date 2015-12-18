/**
  * @file	WorkerThread.cpp
  * @brief	���[�J�[�X���b�h�B
  * @date 2015/08/08 03:16:16
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Worker/Job.h"
#include "Lib/Worker/WorkerChannel.h"
#include "Lib/Worker/WorkerThread.h"

/**
 * @brief	�R���X�g���N�^�B
 * @param	_pcChannel	: �d���̎�挳�B
 */
CWorkerThread::CWorkerThread( CWorkerChannel* _pcChannel )
	: CThread()
	, m_pcChannel( _pcChannel )
	, m_bRequestEnd( false )
	, m_bWait( true )
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CWorkerThread::~CWorkerThread()
{
}

/**
 * @brief	�R�[���o�b�N�֐��B
 */
void CWorkerThread::ThreadCallback()
{
	ASSERT( m_pcChannel );
	if (nullptr == m_pcChannel)
	{
		return;	// failsafe
	}
	while (false == m_bRequestEnd)
	{
		CJob* pcJob = m_pcChannel->TakeJob();

		if (nullptr == pcJob)
		{
			m_bWait = true;
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
			continue;
		}

		m_bWait = false;
		CDebugProcessTime cTime( __FUNCTION__ );
		pcJob->Run();
		pcJob->SetEnd( true );
	}
}
