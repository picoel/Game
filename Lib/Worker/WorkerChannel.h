/**
  * @file	WorkerChannel.h
  * @brief	WorkerThreadにおけるChannel。
  * @date 2015/08/08 02:55:10
  */

#ifndef INCLUDE_LIB_WORKER_CHANNEL_H
#define INCLUDE_LIB_WORKER_CHANNEL_H

#include "Lib/Utility/List.h"
#include "Lib/Thread/CriticalSection.h"

class  CJob;

/*
 * @class CWorkerChannel
 * @brief 仕事を受け取り、WorkerThreadに伝達する。
 */
class CWorkerChannel
{
public:
	/// コンストラクタ。
	CWorkerChannel();
	/// デストラクタ。
	virtual ~CWorkerChannel();

	/// 仕事を追加。
	void PutJob( CJob* _pcJob );		// WindowsAPIでAddJobが定義されているため、PutJobという名前にする。
	/// 仕事を取得。
	CJob* TakeJob();
private:
	CQueue< CJob* >		m_cQueueJob;
	CCriticalSection	m_cCriticalSection;
};

#endif // #ifndef INCLUDE_LIB_WORKER_CHANNEL_H