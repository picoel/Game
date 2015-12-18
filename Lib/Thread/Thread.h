/**
  * @file	Thread.h
  * @brief	�X���b�h����B
  * @date 2015/05/24 04:45:21
  */

#ifndef INCLUDE_LIB_THREAD_THREAD_H
#define INCLUDE_LIB_THREAD_THREAD_H

#include <thread>

/*
 * @class CThread
 * @brief �X���b�h����B
 */
class CThread
{
public:
	/// �R���X�g���N�^�B
	CThread();
	/// �f�X�g���N�^�B
	virtual ~CThread();

	/// �X���b�h�J�n�B
	void Run();
	/// �X���b�h�̏I���҂��B
	void WaitEnd();

	/// �J�n�����X���b�h����Ă΂��R�[���o�b�N�֐��B
	virtual void ThreadCallback(){}

private:
	std::thread		m_cThread;

	bool			m_bStartThread;
};

#endif // #ifndef INCLUDE_LIB_THREAD_THREAD_H