/**
  * @file	WorkerThread.h
  * @brief	ワーカースレッド。
  * @date 2015/08/08 03:16:16
  */

#ifndef INCLUDE_LIB_WORKER_THREAD_H
#define INCLUDE_LIB_WORKER_THREAD_H

#include "Lib/Thread/Thread.h"

class CWorkerChannel;

/*
 * @class CWorkerThread
 * @brief ワーカースレッド。
 */
class CWorkerThread : public CThread
{
public:
	/// コンストラクタ。
	CWorkerThread( CWorkerChannel* _pcChannel );
	/// デストラクタ。
	virtual ~CWorkerThread();

	/// コールバック関数。
	virtual void ThreadCallback() override;

	/// 終了リクエスト。
	void RequestEnd(){ m_bRequestEnd = true; }

	/// 待機中か。
	bool IsWait() const{ return m_bWait; }

private:
	/// 待機中か設定。
	void SetWait( bool _bWait );

	CWorkerChannel* m_pcChannel;
	bool			m_bRequestEnd;
	bool			m_bWait;
};

#endif // #ifndef INCLUDE_LIB_WORKER_THREAD_H
