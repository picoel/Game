/**
  * @file	WorkerManager.cpp
  * @brief	ワーカースレッドの管理クラス。
  * @date 2015/08/08 03:36:41
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Worker/Job.h"
#include "Lib/Worker/WorkerManager.h"
#include "Lib/Worker/WorkerThread.h"

/**
 * @brief	コンストラクタ。
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
 * @brief	デストラクタ。
 */
CWorkerManager::~CWorkerManager()
{
	if (m_pcWorkerArray)
	{
		// ワーカースレッドを停止させる。
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
 * @brief	仕事をリクエスト。
 * @param	_pcJob	: 仕事。
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
 * @brief	WorkerThreadが全て待機中か。
 * @retval	bool	: trueなら全て待機中。
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
