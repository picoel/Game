/**
  * @file	FileReader.cpp
  * @brief	�t�@�C���ǂݍ��݃N���X�B
  * @date	2015/06/29 03:58:07
  */

#include "Lib/LibPrecompile.h"

#include "Lib/File/FileReader.h"
#include "Lib/File/FileReadManager.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_psFileName	: �ǂݍ��ރt�@�C���l�[���B
 */
CFileReader::CFileReader( const TChar* _psFileName )
	: m_cFileName( _psFileName )
	, m_bIsReadEnd( false )
{
	auto* pcFileReadManager = CFileReadManager::GetInstance();
	ASSERT( pcFileReadManager );
	if (pcFileReadManager)
	{
		pcFileReadManager->Request( this );
	}
}
