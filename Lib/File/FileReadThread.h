/**
  * @file	FileReadThread.h
  * @brief	�񓯊��t�@�C���ǂݍ��݃X���b�h�B
  * @date	2015/06/29 05:35:57
  */

#ifndef INCLUDE_LIB_FILE_FILEREADTHREAD_H
#define INCLUDE_LIB_FILE_FILEREADTHREAD_H

#include "Lib/String/String.h"
#include "Lib/Thread/Thread.h"
#include "Lib/Thread/CriticalSection.h"

/*
 * @class CFileReadThread
 * @brief �񓯊��t�@�C���ǂݍ��݃X���b�h�B
 */
class CFileReadThread	: public CThread
{
public:
	/// �R���X�g���N�^�B
	CFileReadThread();
	/// �f�X�g���N�^�B
	virtual ~CFileReadThread();

	/// �J�n�����X���b�h����Ă΂��R�[���o�b�N�֐��B
	virtual void ThreadCallback() override;

	/// �t�@�C���ǂݍ��݃��N�G�X�g�B
	void Request( const TChar* _psFileName );
	/// �X���b�h�I�����N�G�X�g�B
	void RequestEndThread()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		m_bRequestEnd = true;
	}

	/// �ǂݍ��݂��I���������B
	bool IsReadEnd()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		return m_bIsReadEnd; 
	}
	/// �ǂݍ��񂾃f�[�^���擾�B
	void* GetData()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		return m_pData;
	}
	/// �ǂݍ��񂾃f�[�^�T�C�Y���擾�B
	USize GetSize()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		return m_uSize;
	}

private:
	CTString				m_cFileName;
	bool					m_bIsRequest;
	bool					m_bIsReadEnd;
	bool					m_bRequestEnd;

	void*					m_pData;
	USize					m_uSize;
	CCriticalSection		m_cCriticalSection;
};

#endif // #ifndef INCLUDE_LIB_FILE_FILEREADTHREAD_H
