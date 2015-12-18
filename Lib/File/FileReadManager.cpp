/**
  * @file	FileReadManager.cpp
  * @brief	�t�@�C���ǂݍ��݊Ǘ��N���X�B
  * @date	2015/06/29 03:56:12
  */

#include "Lib/LibPrecompile.h"
#include "Lib/File/FileReader.h"
#include "Lib/File/FileReadManager.h"
#include "Lib/File/FileReadThread.h"
#include "Lib/File/JobFileRead.h"
#include "Lib/Worker/Worker.h"

/**
 * @brief	�R���X�g���N�^�B
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
 * @brief	�f�X�g���N�^�B
 */
CFileReadManager::~CFileReadManager()
{
	for (auto* pcJob : m_cJobList)
	{
		if (nullptr == pcJob)
		{
			continue;
		}
		
		// �W���u����������̂�҂B
		while (false == pcJob->IsEnd())
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		}

		P_DELETE( pcJob );
	}
}

/**
 * @brief		�t�@�C���ǂݍ��݃��N�G�X�g�B
 * @param[in]	_pcFileReader	: �t�@�C���ǂݍ��݃N���X�ւ̃|�C���^�B
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
 * @brief	�A�N�V���������B
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
