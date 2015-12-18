/**
  * @file	PMDReader.h
  * @brief	PMD�t�@�C���ǂݍ��݁B
  * @data 2015/12/02 10:41:52
  */

#ifndef INCLUDE_LIB_PMD_PMDREADER_H
#define INCLUDE_LIB_PMD_PMDREADER_H

#include "Lib/File/FileReader.h"

/*
 * @class CPMDReader
 * @brief PMD�t�@�C���ǂݍ��݁B
 */
class CPMDReader : public CFileReader
{
public:
	/// �R���X�g���N�^�B
	CPMDReader( const TChar* _psFileName );
	/// �f�X�g���N�^�B
	virtual ~CPMDReader();

	/// �ǂݍ��݊������̏����B
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// PMD�f�[�^�̎擾�B
	const meshio::pmd::IO& GetPMDData() const{ return m_stData; }

private:
	meshio::pmd::IO	m_stData;
};

#endif // #ifndef INCLUDE_LIB_PMD_PMDREADER_H