/**
  * @file	PMDReader.cpp
  * @brief	PMD�t�@�C���ǂݍ��݁B
  * @data 2015/12/02 10:41:52
  */

#include "Lib/LibPrecompile.h"
#include "Lib/PMD/PMDReader.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_psFileName	: �ǂݍ��ރt�@�C�����B
 */
CPMDReader::CPMDReader( const TChar* _psFileName )
	: CFileReader( _psFileName )
	, m_stData()
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CPMDReader::~CPMDReader()
{
}

/**
 * @brief		�ǂݍ��݊������̏����B
 * @param[in]	_pData	: �ǂݍ��񂾃f�[�^�B
 * @param[in]	_uSize	: �f�[�^�T�C�Y�B
 */
void CPMDReader::ReadEndProcess( const void* _pData, USize _uSize )
{
	ASSERT( _pData );
	if (nullptr == _pData)
	{
		return;	// failsafe
	}

	ASSERT( 0 < _uSize );
	if (_uSize <= 0)
	{
		return;	// failsafe
	}

	meshio::binary::MemoryReader cMemReader( s_cast<const char*>(_pData), _uSize );
	m_stData.read( cMemReader );

	Log( "PMDReadEnd %s", m_stData.name );
}
