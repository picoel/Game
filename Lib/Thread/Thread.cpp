/**
  * @file	Thread.cpp
  * @brief	�X���b�h����B
  * @date 2015/05/24 04:57:54
  */

#include "Lib/LibPrecompile.h"
#include "Lib/Thread/Thread.h"

/**
 * @brief		�R���X�g���N�^�B
 */
CThread::CThread()
	: m_cThread()
	, m_bStartThread( false )
{
}

/**
 * @brief		�f�X�g���N�^�B
 */
CThread::~CThread()
{
	if (m_cThread.joinable())
	{
		m_cThread.join();
	}
}

/**
 * @brief		�X���b�h�J�n�B
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
 * @brief		�X���b�h�̏I���҂��B
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
