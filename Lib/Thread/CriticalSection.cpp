/**
  * @file	CriticalSection.cpp
  * @brief	クリティカルセクション制御。
  * @date 2015/05/10 02:57:00
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Thread/CriticalSection.h"

/**
 * @brief	コンストラクタ。
 */
CCriticalSection::CCriticalSection()
	: m_stCriticalSection()
{
	InitializeCriticalSection( &m_stCriticalSection );
}

/**
 * @brief	デストラクタ。
 */
CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection( &m_stCriticalSection );
}

/**
 * @brief	クリティカルセクション開始。
 */
void CCriticalSection::Enter()
{
	::EnterCriticalSection( &m_stCriticalSection );
}

/**
 * @brief	クリティカルセクション終了。
 */
void CCriticalSection::Leave()
{
	::LeaveCriticalSection( &m_stCriticalSection );
}



/**
 * @brief		コンストラクタ。
 * @param[in]	_pcCriticalSection	: クリティカルセクション。
 */
CCriticalSectionBlock::CCriticalSectionBlock( CCriticalSection* _pcCriticalSection )
	: m_pcCriticalSection( _pcCriticalSection )
{
	ASSERT( m_pcCriticalSection );
	if (m_pcCriticalSection)
	{
		m_pcCriticalSection->Enter();
	}
}

/**
 * @brief		デストラクタ。
 */
CCriticalSectionBlock::~CCriticalSectionBlock()
{
	if (m_pcCriticalSection)
	{
		m_pcCriticalSection->Leave();
	}
}
