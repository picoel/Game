/**
  * @file	MainLoopThread.cpp
  * @brief	メインループ制御スレッド。
  * @data	2015/11/15 18:47:28
  */
#include "Lib/LibPrecompile.h"

#include "Lib/MainLoop/MainLoopThread.h"

#include "Lib/Object/ActionList.h"
#include "Lib/Object/DrawList.h"
#include "Lib/Render/RenderContext.h"
#include "Lib/Render/RenderContextFactory.h"
#include "Lib/Worker/Worker.h"

/**
 * @brief	コンストラクタ。
 */
CMainLoopThread::CMainLoopThread()
	: CSingleton<CMainLoopThread>()
	, CThread()
	, m_pcRenderContext( nullptr )
	, m_pcSequenceControl( nullptr )
	, m_bEnd( false )
{
}

/**
 * @brief	デストラクタ。
 */
CMainLoopThread::~CMainLoopThread()
{
	P_DELETE( m_pcSequenceControl );
	P_DELETE( m_pcRenderContext );
}

/**
 * @brief		初期化。
 * @param[in]	_rstParam	: 初期化用パラメータ。
 */
void CMainLoopThread::Init( const StInitParam& _rstParam )
{
	ASSERT( _rstParam.m_pcRenderContextFactory );
	if (nullptr == _rstParam.m_pcRenderContextFactory)
	{
		return;	// failsafe
	}

	ASSERT( nullptr == m_pcRenderContext );
	P_DELETE( m_pcRenderContext );
	m_pcRenderContext = _rstParam.m_pcRenderContextFactory->Create();

	ASSERT( nullptr == m_pcSequenceControl );
	P_DELETE( m_pcSequenceControl );
	m_pcSequenceControl = pnew CSequenceControl( _rstParam.m_stSequenceControlParam );
}

/**
 * @brief	メインループ。
 */
void CMainLoopThread::MainLoop()
{
	ASSERT( m_pcRenderContext );
	if (nullptr == m_pcRenderContext)
	{
		return;	// failsafe
	}

	ASSERT( m_pcSequenceControl );
	if (nullptr == m_pcSequenceControl)
	{
		return;	// failsafe
	}

	CWorker* pcWorker = CWorker::GetInstance();
	ASSERT( pcWorker );
	if (nullptr == pcWorker)
	{
		return; // failsafe
	}

	// 無限ループ。
	while (true)
	{
		if (IsEnd())
		{
			break;
		}

		m_pcSequenceControl->LoopStartAct();

		ExecAction();
		ExecDraw();

		pcWorker->Sync();

		LoopEndAct();
	}
}

/**
 * @brief		アクションを実行。
 */
void CMainLoopThread::ExecAction()
{
	ASSERT( m_pcSequenceControl );
	if (nullptr == m_pcSequenceControl)
	{
		return;	// failsafe
	}

	CActionList* pcActionList = CActionList::GetInstance();
	ASSERT( pcActionList );
	if (nullptr == pcActionList)
	{
		return;	// failsafe
	}

	const U32 uActionLvMax = pcActionList->GetMaxLv();
	for (U32 ii = 0; ii < uActionLvMax; ++ii)
	{
		m_pcSequenceControl->ActionLvInit( ii );
		pcActionList->ExecAction( ii );
	}
}

/**
 * @brief		描画処理。
 */
void CMainLoopThread::ExecDraw()
{
	ASSERT( m_pcRenderContext );
	if (nullptr == m_pcRenderContext)
	{
		return;	// failsafe
	}

	ASSERT( m_pcSequenceControl );
	if (nullptr == m_pcSequenceControl)
	{
		return;	// failsafe
	}

	CDrawList* pcDrawList = CDrawList::GetInstance();
	ASSERT( pcDrawList );
	if (nullptr == pcDrawList)
	{
		return; // failsafe
	}

	// 使用不可なら描画しない。
	if (!m_pcRenderContext->IsEnabled())
	{
		return;
	}
	
	m_pcRenderContext->Clear();

	const U32 uDrawLvMax = pcDrawList->GetMaxLv();
	for (U32 ii = 0; ii < uDrawLvMax; ++ii)
	{
		m_pcSequenceControl->DrawLvInit( ii, m_pcRenderContext );
		pcDrawList->ExecDraw( ii, m_pcRenderContext );
	}

	m_pcRenderContext->Render();
}

/**
 * @brief		ループ終了時の処理。
 */
void CMainLoopThread::LoopEndAct()
{
	ASSERT( m_pcSequenceControl );
	if (nullptr == m_pcSequenceControl)
	{
		return;	// failsafe
	}

	CActionList* pcActionList = CActionList::GetInstance();
	ASSERT( pcActionList );
	if (nullptr == pcActionList)
	{
		return;	// failsafe
	}

	CDrawList* pcDrawList = CDrawList::GetInstance();
	ASSERT( pcDrawList );
	if (nullptr == pcDrawList)
	{
		return; // failsafe
	}

	m_pcSequenceControl->LoopEndAct();
	pcActionList->LoopEndAct();
	pcDrawList->LoopEndAct();
}
