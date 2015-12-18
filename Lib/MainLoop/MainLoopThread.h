/**
  * @file	MainLoopThread.h
  * @brief	���C�����[�v����X���b�h�B
  * @data	2015/11/15 18:47:28
  */
#ifndef INCLUDE_LIB_MAINLOOP_THREAD_H
#define INCLUDE_LIB_MAINLOOP_THREAD_H

#include "Lib/Sequence/SequenceControl.h"
#include "Lib/Thread/CriticalSection.h"
#include "Lib/Thread/Thread.h"
#include "Lib/Utility/Singleton.h"

class IRenderContext;
class IRenderContextFactory;

/*
 * @class CMainLoopThread
 * @brief ���C�����[�v����B
 */
class CMainLoopThread 
	: public CSingleton< CMainLoopThread >
	, public CThread
{
	friend CSingleton< CMainLoopThread >;

public:
	/// �������p�p�����[�^�B
	struct StInitParam
	{
		IRenderContextFactory*			m_pcRenderContextFactory;
		CSequenceControl::StInitParam	m_stSequenceControlParam;

		void Init()
		{
			m_pcRenderContextFactory = nullptr;
			m_stSequenceControlParam.Init();
		}
	};

private:
	/// �R���X�g���N�^�B
	CMainLoopThread();

public:
	/// �f�X�g���N�^�B
	virtual ~CMainLoopThread();

	/// �������B
	void Init( const StInitParam& _rstParam );

	/// �X���b�h�Ŏ��s�����֐��B
	virtual void ThreadCallback() override{ MainLoop(); }

	/// ���C�����[�v�B
	void MainLoop();

	/// �I���B
	void End(){ m_bEnd = true; }
	/// �I���������B
	bool IsEnd() const{ return m_bEnd; }

private:
	/// �A�N�V���������B
	void ExecAction();
	/// �`�揈���B
	void ExecDraw();

	/// ���[�v�I�����̏����B
	void LoopEndAct();

private:
	IRenderContext*		m_pcRenderContext;
	CSequenceControl*	m_pcSequenceControl;

	bool				m_bEnd;
};

#endif // #ifndef INCLUDE_LIB_MAINLOOP_THREAD_H