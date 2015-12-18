/**
  * @file	FileReadThread.cpp
  * @brief	非同期ファイル読み込みスレッド。
  * @date	2015/06/29 05:35:57
  */

#include "Lib/LibPrecompile.h"

#include <fstream>
#include <iostream>
#include "Lib/File/FileReadThread.h"

/**
 * @brief	コンストラクタ。
 */
CFileReadThread::CFileReadThread()
	: CThread()
	, m_cFileName()
	, m_bIsRequest( false )
	, m_bIsReadEnd( false )
	, m_bRequestEnd( false )
	, m_pData( nullptr )
	, m_uSize( 0 )
	, m_cCriticalSection()
{
}

/**
 * @brief	デストラクタ。
 */
CFileReadThread::~CFileReadThread()
{
	P_DELETE_ARRAY( m_pData );
}

/**
 * @brief	開始したスレッドから呼ばれるコールバック関数。
 */
void CFileReadThread::ThreadCallback()
{
	while (false == m_bRequestEnd)
	{
		if (m_bIsRequest)
		{
			CTString cFileName;
			{
				CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
				P_DELETE_ARRAY( m_pData );
				cFileName = m_cFileName.c_str();
			}

			std::ifstream cIFS( cFileName.c_str(), std::ios::in | std::ios::binary );
			const USize uBegin = cIFS.tellg();
			cIFS.seekg( 0, cIFS.end );
			const USize uEnd = cIFS.tellg();
			const USize uSize = uEnd - uBegin;
			cIFS.clear();
			cIFS.seekg( 0, cIFS.beg );

			ASSERT( 0 < uSize );

			S8* pBuff = nullptr;
			if ( 0 < uSize )
			{
				pBuff = pnew S8[ uSize ];
				cIFS.read( pBuff, uSize );

				Log( "ReadEnd %s[%lldbyte]", cFileName.c_str(), uSize );
			}
			{
				CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
				m_pData = pBuff;
				m_uSize = uSize;
				m_bIsRequest = false;
				m_bIsReadEnd = true;
			}
		}
		else
		{
			std::this_thread::sleep_for( std::chrono::microseconds( 1 ) );
		}
	}
}

/**
 * @brief		ファイル読み込みリクエスト。
 * @param[in]	_psFileName	: 読み込むファイルネーム。
 */
void CFileReadThread::Request( const TChar* _psFileName )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	ASSERT( _psFileName );
	if (nullptr == _psFileName)
	{
		return;	// failsafe
	}
	ASSERT( false == m_bIsRequest );
	if (m_bIsRequest)
	{
		return;	// failsafe
	}

	m_cFileName = _psFileName;
	m_bIsRequest = true;
	m_bIsReadEnd = false;
}

