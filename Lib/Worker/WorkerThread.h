/**
  * @file	WorkerThread.h
  * @brief	���[�J�[�X���b�h�B
  * @date 2015/08/08 03:16:16
  */

#ifndef INCLUDE_LIB_WORKER_THREAD_H
#define INCLUDE_LIB_WORKER_THREAD_H

#include "Lib/Thread/Thread.h"

class CWorkerChannel;

/*
 * @class CWorkerThread
 * @brief ���[�J�[�X���b�h�B
 */
class CWorkerThread : public CThread
{
public:
	/// �R���X�g���N�^�B
	CWorkerThread( CWorkerChannel* _pcChannel );
	/// �f�X�g���N�^�B
	virtual ~CWorkerThread();

	/// �R�[���o�b�N�֐��B
	virtual void ThreadCallback() override;

	/// �I�����N�G�X�g�B
	void RequestEnd(){ m_bRequestEnd = true; }

	/// �ҋ@�����B
	bool IsWait() const{ return m_bWait; }

private:
	/// �ҋ@�����ݒ�B
	void SetWait( bool _bWait );

	CWorkerChannel* m_pcChannel;
	bool			m_bRequestEnd;
	bool			m_bWait;
};

#endif // #ifndef INCLUDE_LIB_WORKER_THREAD_H
