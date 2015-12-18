/**
  * @file	WorkerManager.cpp
  * @brief	���[�J�[�X���b�h�̊Ǘ��N���X�B
  * @date 2015/08/08 03:36:41
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Worker/Job.h"
#include "Lib/Worker/WorkerManager.h"
#include "Lib/Worker/WorkerThread.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CWorkerManager::CWorkerManager( U32 _uWorkerNum )
	: m_cChannel()
	, m_pcWorkerArray( nullptr )
	, m_uWorkerNum( _uWorkerNum )
{
	ASSERT( 0 < _uWorkerNum );
	if (_uWorkerNum <= 0)
	{
		return;	// failsafe
	}

	m_uWorkerNum = _uWorkerNum;
	ASSERT( nullptr == m_pcWorkerArray );
	P_DELETE_ARRAY( m_pcWorkerArray );
	m_pcWorkerArray = pnew CWorkerThread*[ m_uWorkerNum ];
	for (U32 ii = 0; ii < m_uWorkerNum; ++ii)
	{
		m_pcWorkerArray[ ii ] = pnew CWorkerThread( &m_cChannel );
		m_pcWorkerArray[ ii ]->Run();
	}
}

/**
 * @brief	�f�X�g���N�^�B
 */
CWorkerManager::~CWorkerManager()
{
	if (m_pcWorkerArray)
	{
		// ���[�J�[�X���b�h���~������B
		for (U32 ii = 0; ii < m_uWorkerNum; ++ii)
		{
			if (m_pcWorkerArray[ ii ])
			{
				m_pcWorkerArray[ ii ]->RequestEnd();
				P_DELETE( m_pcWorkerArray[ ii ] );
			}
		}

		P_DELETE_ARRAY( m_pcWorkerArray );
	}
}

/**
 * @brief	�d�������N�G�X�g�B
 * @param	_pcJob	: �d���B
 */
void CWorkerManager::RequestJob( CJob* _pcJob )
{
	ASSERT( _pcJob );
	if (nullptr == _pcJob)
	{
		return;	// failsafe
	}

	m_cChannel.PutJob( _pcJob );
}

/**
 * @brief	WorkerThread���S�đҋ@�����B
 * @retval	bool	: true�Ȃ�S�đҋ@���B
 */
bool CWorkerManager::IsWaitAll() const
{
	if (nullptr == m_pcWorkerArray)
	{
		return true;
	}

	bool bRet = true;
	for (U32 ii = 0; ii < m_uWorkerNum; ++ii)
	{
		if ( nullptr == m_pcWorkerArray[ ii ])
		{
			continue;
		}

		if ( false == m_pcWorkerArray[ ii ]->IsWait())
		{
			bRet = false;
			break;
		}
	}

	return bRet;
}
