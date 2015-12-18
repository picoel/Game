/**
  * @file	CriticalSection.cpp
  * @brief	�N���e�B�J���Z�N�V��������B
  * @date 2015/05/10 02:57:00
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Thread/CriticalSection.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CCriticalSection::CCriticalSection()
	: m_stCriticalSection()
{
	InitializeCriticalSection( &m_stCriticalSection );
}

/**
 * @brief	�f�X�g���N�^�B
 */
CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection( &m_stCriticalSection );
}

/**
 * @brief	�N���e�B�J���Z�N�V�����J�n�B
 */
void CCriticalSection::Enter()
{
	::EnterCriticalSection( &m_stCriticalSection );
}

/**
 * @brief	�N���e�B�J���Z�N�V�����I���B
 */
void CCriticalSection::Leave()
{
	::LeaveCriticalSection( &m_stCriticalSection );
}



/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_pcCriticalSection	: �N���e�B�J���Z�N�V�����B
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
 * @brief		�f�X�g���N�^�B
 */
CCriticalSectionBlock::~CCriticalSectionBlock()
{
	if (m_pcCriticalSection)
	{
		m_pcCriticalSection->Leave();
	}
}
