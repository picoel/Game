/**
  * @file	FileReader.h
  * @brief	�t�@�C���ǂݍ��݃N���X�B
  * @date	2015/06/29 03:58:07
  */

#ifndef INCLUDE_LIB_FILE_FILEREADER_H
#define INCLUDE_LIB_FILE_FILEREADER_H

#include "Lib/String/String.h"

/*
 * @class	CFileReader
 * @brief	�t�@�C���ǂݍ��݃N���X�B
 */
class CFileReader
{
public:
	/// �R���X�g���N�^�B
	CFileReader( const TChar* _psFileName );
	/// �f�X�g���N�^�B
	virtual ~CFileReader(){}

	/// �ǂݍ��݊������̏����B
	virtual void ReadEndProcess( const void* _pData, USize _uSize ){}
	/// �ǂݍ��݊������̏���(���C���X���b�h�Ɠ���)�B
	virtual void ReadEndProcessSync(){}

	/// �ǂݍ��ރt�@�C�������擾�B
	const TChar* GetFileName() const{ return m_cFileName.c_str(); }

	/// �ǂݍ��݂������������B
	bool IsReadEnd() const{ return m_bIsReadEnd; }
	/// �ǂݍ��݂������������ݒ�B
	void SetReadEnd( bool _bEnd ){ m_bIsReadEnd = _bEnd; }

private:
	CTString	m_cFileName;
	bool		m_bIsReadEnd;
};

#endif // #ifndef INCLUDE_LIB_FILE_FILEREADER_H
