/**
  * @file	Job.h
  * @brief	WorkerThread�ōs���d���N���X�B
  * @date	2015/08/08 02:47:32
  */

#ifndef INCLUDE_LIB_WORKER_JOB_H
#define INCLUDE_LIB_WORKER_JOB_H

/*
 * @class CJob
 * @brief �d���N���X�B
 */
class CJob
{
public:
	/// �R���X�g���N�^�B
	CJob() : m_bEnd( false ){}
	/// �f�X�g���N�^�B
	virtual ~CJob(){}

	/// ���[�J�[�X���b�h�ōs�������B
	virtual void Run(){}

	/// �I���������B
	bool IsEnd() const{ return m_bEnd; }
	/// �I���������ݒ�B
	void SetEnd( bool _bEnd ){ m_bEnd = _bEnd; }

private:
	bool	m_bEnd;
};

#endif // #ifndef INCLUDE_LIB_WORKER_JOB_H