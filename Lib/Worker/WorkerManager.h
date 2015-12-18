/**
  * @file	WorkerManager.h
  * @brief	���[�J�[�X���b�h�̊Ǘ��N���X�B
  * @date 2015/08/08 03:36:41
  */

#ifndef INCLUDE_WORKER_MANAGER_H
#define INCLUDE_WORKER_MANAGER_H

#include "Lib/Worker/WorkerChannel.h"

class CJob;
class CWorkerThread;

/*
 * @class CWorkerManager
 * @brief ���[�J�[�X���b�h�̊Ǘ��B
 */
class CWorkerManager
{
public:
	/// �R���X�g���N�^�B
	CWorkerManager( U32 _uWorkerNum );
	/// �f�X�g���N�^�B
	virtual ~CWorkerManager();

	/// �d�������N�G�X�g�B
	void RequestJob( CJob* _pcJob );
	
	/// WorkerThread���S�đҋ@�����B
	bool IsWaitAll() const;

private:
	CWorkerChannel	m_cChannel;
	CWorkerThread**	m_pcWorkerArray;
	U32				m_uWorkerNum;
};

#endif // #ifndef INCLUDE_WORKER_MANAGER_H