/**
  * @file	FileReader.cpp
  * @brief	ファイル読み込みクラス。
  * @date	2015/06/29 03:58:07
  */

#include "Lib/LibPrecompile.h"

#include "Lib/File/FileReader.h"
#include "Lib/File/FileReadManager.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_psFileName	: 読み込むファイルネーム。
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
