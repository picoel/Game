/**
  * @file	JobFileRead.h
  * @brief	�t�@�C���ǂݍ��݃W���u�N���X�B
  * @date	2015/08/09 00:59:20
  */

#ifndef INCLUDE_LIB_FILE_JOB_FILEREAD_H
#define INCLUDE_LIB_FILE_JOB_FILEREAD_H

#include "Lib/Worker/Job.h"

class CFileReader;

/*
 * @class CJobFileRead
 * @brief �t�@�C���ǂݍ��݃W���u�B
 */
class CJobFileRead : public CJob
{
public:
	/// �R���X�g���N�^�B
	CJobFileRead( CFileReader* _pcReader );
	/// �f�X�g���N�^�B
	virtual ~CJobFileRead(){}

	/// ���[�J�[�X���b�h�ōs�������B
	virtual void Run() override;

	/// �t�@�C�����[�_�[���擾�B
	CFileReader* GetFileReader() const{ return m_pcReader; }

private:
	CFileReader*	m_pcReader;
};

#endif // #ifndef INCLUDE_LIB_FILE_JOB_FILEREAD_H