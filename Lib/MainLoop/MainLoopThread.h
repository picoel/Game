/**
  * @file	MainLoopThread.h
  * @brief	メインループ制御スレッド。
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
 * @brief メインループ制御。
 */
class CMainLoopThread 
	: public CSingleton< CMainLoopThread >
	, public CThread
{
	friend CSingleton< CMainLoopThread >;

public:
	/// 初期化用パラメータ。
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
	/// コンストラクタ。
	CMainLoopThread();

public:
	/// デストラクタ。
	virtual ~CMainLoopThread();

	/// 初期化。
	void Init( const StInitParam& _rstParam );

	/// スレッドで実行される関数。
	virtual void ThreadCallback() override{ MainLoop(); }

	/// メインループ。
	void MainLoop();

	/// 終了。
	void End(){ m_bEnd = true; }
	/// 終了したか。
	bool IsEnd() const{ return m_bEnd; }

private:
	/// アクション処理。
	void ExecAction();
	/// 描画処理。
	void ExecDraw();

	/// ループ終了時の処理。
	void LoopEndAct();

private:
	IRenderContext*		m_pcRenderContext;
	CSequenceControl*	m_pcSequenceControl;

	bool				m_bEnd;
};

#endif // #ifndef INCLUDE_LIB_MAINLOOP_THREAD_H