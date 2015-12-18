/**
  * @file	Worker.h
  * @brief	ワーカースレッド。
  * @date 2015/08/28 02:01:58
  */

#ifndef INCLUDE_LIB_WORKER_H
#define INCLUDE_LIB_WORKER_H

#include "Lib/Utility/Singleton.h"

class CWorkerManager;
class CJob;

/*
 * @class CWorker
 * @brief ワーカースレッド。
 */
class CWorker : public CSingleton<CWorker>
{
private:
	friend CSingleton<CWorker>;

	/// コンストラクタ。
	CWorker();
public:
	/// 初期化用パラメータ。
	struct StInitParam
	{
		U32	m_uWorkerSyncNum;
		U32 m_uWorkerUnSyncNum;

		void Init()
		{
			m_uWorkerSyncNum = 0;
			m_uWorkerUnSyncNum = 0;
		}
	};

	/// デストラクタ。
	virtual ~CWorker();

	/// 初期化。
	void Init( const StInitParam& _rstInit );

	/// リクエスト。
	static void RequestJob( CJob* _pcJob, bool _bSync );
	
	/// 同期。
	static void Sync();

private:
	CWorkerManager* m_pcWorkerManagerSync;
	CWorkerManager* m_pcWorkerManagerUnSync;
};

#endif // #ifndef INCLUDE_LIB_WORKER_H
