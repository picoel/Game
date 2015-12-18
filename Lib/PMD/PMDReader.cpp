/**
  * @file	PMDReader.cpp
  * @brief	PMDファイル読み込み。
  * @data 2015/12/02 10:41:52
  */

#include "Lib/LibPrecompile.h"
#include "Lib/PMD/PMDReader.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_psFileName	: 読み込むファイル名。
 */
CPMDReader::CPMDReader( const TChar* _psFileName )
	: CFileReader( _psFileName )
	, m_stData()
{
}

/**
 * @brief	デストラクタ。
 */
CPMDReader::~CPMDReader()
{
}

/**
 * @brief		読み込み完了時の処理。
 * @param[in]	_pData	: 読み込んだデータ。
 * @param[in]	_uSize	: データサイズ。
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
