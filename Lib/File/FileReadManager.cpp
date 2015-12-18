/**
  * @file	FileReadManager.cpp
  * @brief	ファイル読み込み管理クラス。
  * @date	2015/06/29 03:56:12
  */

#include "Lib/LibPrecompile.h"
#include "Lib/File/FileReader.h"
#include "Lib/File/FileReadManager.h"
#include "Lib/File/FileReadThread.h"
#include "Lib/File/JobFileRead.h"
#include "Lib/Worker/Worker.h"

/**
 * @brief	コンストラクタ。
 */
CFileReadManager::CFileReadManager()
	: CSingleton<CFileReadManager>()
	, CAction( 0 )
	, m_cJobList()
{
}

CFileReadManager::CFileReadManager( const StInitParam& _rstParam )
	: CSingleton<CFileReadManager>()
	, CAction( _rstParam.m_uActionLv )
	, m_cJobList()
{
}

/**
 * @brief	デストラクタ。
 */
CFileReadManager::~CFileReadManager()
{
	for (auto* pcJob : m_cJobList)
	{
		if (nullptr == pcJob)
		{
			continue;
		}
		
		// ジョブが完了するのを待つ。
		while (false == pcJob->IsEnd())
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		}

		P_DELETE( pcJob );
	}
}

/**
 * @brief		ファイル読み込みリクエスト。
 * @param[in]	_pcFileReader	: ファイル読み込みクラスへのポインタ。
 */
void CFileReadManager::Request( CFileReader* _pcFileReader )
{
	ASSERT( _pcFileReader );
	if (nullptr == _pcFileReader)
	{
		return;	// failsafe
	}

	CJobFileRead* pcJob = pnew CJobFileRead( _pcFileReader );
	CWorker::RequestJob( pcJob, false );

	m_cJobList.push_back( pcJob );
}

/**
 * @brief	アクション処理。
 */
void CFileReadManager::Action()
{
	if (m_cJobList.empty())
	{
		return;
	}

	auto cItBegin = m_cJobList.begin();
	auto cItEnd = m_cJobList.end();
	for (auto cIt = cItBegin; cIt != cItEnd; ++cIt)
	{
		auto* pcJob = *cIt;
		ASSERT( pcJob );
		if (nullptr == pcJob)
		{
			continue;	// failsafe
		}

		if (pcJob->IsEnd())
		{
			auto* pcReader = pcJob->GetFileReader();

			ASSERT( pcReader );
			if (pcReader)
			{
				pcReader->SetReadEnd( true );
				pcReader->ReadEndProcessSync();
			}

			P_DELETE( pcJob );
			*cIt = nullptr;
		}
	}

	auto cItBeginRemove = std::remove_if( cItBegin, cItEnd,
		[]( CJobFileRead* _pcJob )->bool{ return nullptr == _pcJob; } );
	m_cJobList.erase( cItBeginRemove, cItEnd );
}
