/**
  * @file	Worker.h
  * @brief	���[�J�[�X���b�h�B
  * @date 2015/08/28 02:01:58
  */

#ifndef INCLUDE_LIB_WORKER_H
#define INCLUDE_LIB_WORKER_H

#include "Lib/Utility/Singleton.h"

class CWorkerManager;
class CJob;

/*
 * @class CWorker
 * @brief ���[�J�[�X���b�h�B
 */
class CWorker : public CSingleton<CWorker>
{
private:
	friend CSingleton<CWorker>;

	/// �R���X�g���N�^�B
	CWorker();
public:
	/// �������p�p�����[�^�B
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

	/// �f�X�g���N�^�B
	virtual ~CWorker();

	/// �������B
	void Init( const StInitParam& _rstInit );

	/// ���N�G�X�g�B
	static void RequestJob( CJob* _pcJob, bool _bSync );
	
	/// �����B
	static void Sync();

private:
	CWorkerManager* m_pcWorkerManagerSync;
	CWorkerManager* m_pcWorkerManagerUnSync;
};

#endif // #ifndef INCLUDE_LIB_WORKER_H
