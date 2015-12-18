/**
  * @file	JobFileRead.cpp
  * @brief	ファイル読み込みジョブクラス。
  * @date	2015/08/09 00:59:20
  */

#include "Lib/LibPrecompile.h"

#include <fstream>
#include <iostream>

#include "Lib/File/JobFileRead.h"
#include "Lib/File/FileReader.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_pcReader	: ファイル読み込みクラス。
 */
CJobFileRead::CJobFileRead( CFileReader* _pcReader )
	: m_pcReader( _pcReader )
{
}

/**
 * @brief	ワーカースレッドで行う処理。
 */
void CJobFileRead::Run()
{
	ASSERT( m_pcReader );
	if (nullptr == m_pcReader)
	{
		return;	// failsafe
	}

	std::ifstream cIFS( m_pcReader->GetFileName(), std::ios::in | std::ios::binary );
	const USize uBegin = cIFS.tellg();
	cIFS.seekg( 0, cIFS.end );
	const USize uEnd = cIFS.tellg();
	const USize uSize = uEnd - uBegin;
	cIFS.clear();
	cIFS.seekg( 0, cIFS.beg );

	ASSERT( 0 < uSize );

	if ( 0 < uSize )
	{
		S8* pBuff = ptempnew S8[ uSize ];
		cIFS.read( pBuff, uSize );

		Log( "ReadEnd %s[%lldbyte]", m_pcReader->GetFileName(), uSize );
		m_pcReader->ReadEndProcess( pBuff, uSize );
		P_DELETE_ARRAY( pBuff );
	}
}
