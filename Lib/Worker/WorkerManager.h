/**
  * @file	WorkerManager.h
  * @brief	ワーカースレッドの管理クラス。
  * @date 2015/08/08 03:36:41
  */

#ifndef INCLUDE_WORKER_MANAGER_H
#define INCLUDE_WORKER_MANAGER_H

#include "Lib/Worker/WorkerChannel.h"

class CJob;
class CWorkerThread;

/*
 * @class CWorkerManager
 * @brief ワーカースレッドの管理。
 */
class CWorkerManager
{
public:
	/// コンストラクタ。
	CWorkerManager( U32 _uWorkerNum );
	/// デストラクタ。
	virtual ~CWorkerManager();

	/// 仕事をリクエスト。
	void RequestJob( CJob* _pcJob );
	
	/// WorkerThreadが全て待機中か。
	bool IsWaitAll() const;

private:
	CWorkerChannel	m_cChannel;
	CWorkerThread**	m_pcWorkerArray;
	U32				m_uWorkerNum;
};

#endif // #ifndef INCLUDE_WORKER_MANAGER_H