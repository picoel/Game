/**
  * @file	Thread.h
  * @brief	スレッド制御。
  * @date 2015/05/24 04:45:21
  */

#ifndef INCLUDE_LIB_THREAD_THREAD_H
#define INCLUDE_LIB_THREAD_THREAD_H

#include <thread>

/*
 * @class CThread
 * @brief スレッド制御。
 */
class CThread
{
public:
	/// コンストラクタ。
	CThread();
	/// デストラクタ。
	virtual ~CThread();

	/// スレッド開始。
	void Run();
	/// スレッドの終了待ち。
	void WaitEnd();

	/// 開始したスレッドから呼ばれるコールバック関数。
	virtual void ThreadCallback(){}

private:
	std::thread		m_cThread;

	bool			m_bStartThread;
};

#endif // #ifndef INCLUDE_LIB_THREAD_THREAD_H