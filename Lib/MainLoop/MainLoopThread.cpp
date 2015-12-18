/**
  * @file	MainLoopThread.cpp
  * @brief	���C�����[�v����X���b�h�B
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
 * @brief	�R���X�g���N�^�B
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
 * @brief	�f�X�g���N�^�B
 */
CMainLoopThread::~CMainLoopThread()
{
	P_DELETE( m_pcSequenceControl );
	P_DELETE( m_pcRenderContext );
}

/**
 * @brief		�������B
 * @param[in]	_rstParam	: �������p�p�����[�^�B
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
 * @brief	���C�����[�v�B
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

	// �������[�v�B
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
 * @brief		�A�N�V���������s�B
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
 * @brief		�`�揈���B
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

	// �g�p�s�Ȃ�`�悵�Ȃ��B
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
 * @brief		���[�v�I�����̏����B
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
