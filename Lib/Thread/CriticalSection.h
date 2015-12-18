/**
  * @file	CriticalSection.h
  * @brief	�N���e�B�J���Z�N�V��������B
  * @date 2015/05/10 02:57:00
  */

#ifndef INCLUDE_CRITICALSECTION_H
#define INCLUDE_CRITICALSECTION_H

#include "Lib/LibWindows.h"

/*
 * @class	CCriticalSection
 * @brief	�N���e�B�J���Z�N�V�����B
 */
class CCriticalSection
{
public:
	/// �R���X�g���N�^�B
	CCriticalSection();
	/// �f�X�g���N�^�B
	virtual ~CCriticalSection();

	/// �N���e�B�J���Z�N�V�����J�n�B
	void Enter();
	/// �N���e�B�J���Z�N�V�����I���B
	void Leave();
private:
	CRITICAL_SECTION	m_stCriticalSection;
};

/*
 * @class	CCriticalSectionBlock
 * @brief	�u���b�N���ŃN���e�B�J���Z�N�V�������J�n����B
 * @note	�u���b�N���I������܂�CCriticalSection���������Ă���K�v������B
 */
class CCriticalSectionBlock
{
public:
	/// �R���X�g���N�^�B
	CCriticalSectionBlock( CCriticalSection* _pcCriticalSection );
	/// �f�X�g���N�^�B
	virtual ~CCriticalSectionBlock();

private:
	CCriticalSection*	m_pcCriticalSection;
};

#endif // #ifndef INCLUDE_CRITICALSECTION_H