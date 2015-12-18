/**
  * @file	WorkerChannel.h
  * @brief	WorkerThread�ɂ�����Channel�B
  * @date 2015/08/08 02:55:10
  */

#ifndef INCLUDE_LIB_WORKER_CHANNEL_H
#define INCLUDE_LIB_WORKER_CHANNEL_H

#include "Lib/Utility/List.h"
#include "Lib/Thread/CriticalSection.h"

class  CJob;

/*
 * @class CWorkerChannel
 * @brief �d�����󂯎��AWorkerThread�ɓ`�B����B
 */
class CWorkerChannel
{
public:
	/// �R���X�g���N�^�B
	CWorkerChannel();
	/// �f�X�g���N�^�B
	virtual ~CWorkerChannel();

	/// �d����ǉ��B
	void PutJob( CJob* _pcJob );		// WindowsAPI��AddJob����`����Ă��邽�߁APutJob�Ƃ������O�ɂ���B
	/// �d�����擾�B
	CJob* TakeJob();
private:
	CQueue< CJob* >		m_cQueueJob;
	CCriticalSection	m_cCriticalSection;
};

#endif // #ifndef INCLUDE_LIB_WORKER_CHANNEL_H