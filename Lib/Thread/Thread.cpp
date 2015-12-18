/**
  * @file	Thread.cpp
  * @brief	スレッド制御。
  * @date 2015/05/24 04:57:54
  */

#include "Lib/LibPrecompile.h"
#include "Lib/Thread/Thread.h"

/**
 * @brief		コンストラクタ。
 */
CThread::CThread()
	: m_cThread()
	, m_bStartThread( false )
{
}

/**
 * @brief		デストラクタ。
 */
CThread::~CThread()
{
	if (m_cThread.joinable())
	{
		m_cThread.join();
	}
}

/**
 * @brief		スレッド開始。
 */
void CThread::Run()
{
	ASSERT( !m_bStartThread );
	if (!m_bStartThread)
	{
		m_cThread = std::thread( [ this ]{ this->ThreadCallback(); } );
		m_bStartThread = true;
	}
}

/**
 * @brief		スレッドの終了待ち。
 */
void CThread::WaitEnd()
{
	if ( m_bStartThread )
	{
		ASSERT( m_cThread.joinable() );
		if (m_cThread.joinable())
		{
			m_cThread.join();
			m_bStartThread = false;
		}
	}
}
