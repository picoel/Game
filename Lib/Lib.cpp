/**
  * @file	Lib.cpp
  * @brief	ライブラリを使用するために必要な処理。
  * @date 2015/08/28 02:40:58
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Lib.h"
#include "Lib/DirectX/DirectX.h"
#include "Lib/DirectX/RenderContextFactoryDX11.h"
#include "Lib/File/FileReadManager.h"
#include "Lib/Memory/MemManager.h"
#include "Lib/Object/ActionList.h"
#include "Lib/Worker/Worker.h"

/**
 * @brief	メモリアロケータの初期化。
 * @param	_uMemSize	: メモリサイズ。
 */
void nLib::InitMemAllocator( USize _uMemSize )
{
#if defined(USE_MEMALLOC)
	CMemManager::CreateInstance();
	CMemManager* pcMemManager = CMemManager::GetInstance();
	pcMemManager->Initialize( _uMemSize );
#endif //  #if defined(USE_MEMALLOC)
}

/**
 * @brief	ライブラリの初期化。
 * @param	_rstSetting	: ライブラリ設定。
 */
void nLib::Initialize( const nLib::StLibSetting& _rstSetting )
{
	CActionList::CreateInstance();
	CActionList* pcActionList = CActionList::GetInstance();
	if (pcActionList)
	{
		pcActionList->Init( _rstSetting.m_stActionParam );
	}

	CDrawList::CreateInstance();
	CDrawList* pcDrawList = CDrawList::GetInstance();
	if (pcDrawList)
	{
		pcDrawList->Init( _rstSetting.m_stDrawParam );
	}

	CFileReadManager::CreateInstance( _rstSetting.m_stFileReadParam );

	CWorker::CreateInstance();
	auto* pcWorkerManager = CWorker::GetInstance();
	if (pcWorkerManager)
	{
		pcWorkerManager->Init( _rstSetting.m_stWorkerParam );
	}

	CDirectX::CreateInstance();
	CDirectX* pcDirectX = CDirectX::GetInstance();
	if (pcDirectX)
	{
#if defined( USE_DIRECTX_11 )
		CDirectXDeviceFactoryDX11 cFactory;
		pcDirectX->Init( &cFactory );
#endif // #if defined( USE_DIRECTX_11 )
	}

	CMainLoopThread::CreateInstance();
	CMainLoopThread* pcMainLoopThread = CMainLoopThread::GetInstance();
	if (pcMainLoopThread)
	{
		CMainLoopThread::StInitParam stMainLoopParam;
		stMainLoopParam.Init();

#if defined( USE_DIRECTX_11 )
		CRenderContextFactoryDX11 cRenderContextFactoryDX11( _rstSetting.m_stRenderContextParam );
		stMainLoopParam.m_pcRenderContextFactory = &cRenderContextFactoryDX11;
#endif // #if defined( USE_DIRECTX_11 )

		MemCopy( &stMainLoopParam.m_stSequenceControlParam, &_rstSetting.m_stSequenceParam, sizeof( stMainLoopParam.m_stSequenceControlParam ) );

		pcMainLoopThread->Init( stMainLoopParam );
		pcMainLoopThread->Run();
	}
}

/**
 * @brief	ライブラリの終了処理。
 */
void nLib::Finalize()
{
	CMainLoopThread* pcMainLoopThread = CMainLoopThread::GetInstance();
	if (pcMainLoopThread)
	{
		pcMainLoopThread->End();
		pcMainLoopThread->WaitEnd();
		CMainLoopThread::DestroyInstance();
	}

	CDirectX::DestroyInstance();
	CWorker::DestroyInstance();
	CFileReadManager::DestroyInstance();
	CDrawList::DestroyInstance();
	CActionList::DestroyInstance();
#if defined(USE_MEMALLOC)
	CMemManager* pcMemManager = CMemManager::GetInstance();
	if (pcMemManager)
	{
		pcMemManager->PrintDebugMemoryInfo();
		pcMemManager->PrintDebugMemoryBlock( true, false );
		CMemManager::DestroyInstance();
	}
#endif //  #if defined(USE_MEMALLOC)

}

/**
 * @brief	終了リクエストがあるか。
 * @retval	bool	: trueならばライブラリから終了リクエストがある。
 */
bool nLib::IsEndRequest()
{
	CMainLoopThread* pcMainLoopThread = CMainLoopThread::GetInstance();
	if (nullptr == pcMainLoopThread)
	{
		return true;	// failsafe
	}

	bool bRet = false;
	if (pcMainLoopThread->IsEnd())
	{
		bRet = true;
	}

	return bRet;
}
