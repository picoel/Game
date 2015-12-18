/**
  * @file	RenderThread.cpp
  * @brief	描画用スレッド。
  * @date 2015/05/24 05:14:35
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Render/RenderThread.h"
#include "Lib/Render/RenderContext.h"

#include "Lib/Object/DrawList.h"

#if 0

/**
 * @brief		コンストラクタ。
 * @param[in]	_pcRenderContext	: 描画コンテキスト。
 */
CRenderThread::CRenderThread( IRenderContext* _pcRenderContext )
	: m_pcRenderContext( _pcRenderContext )
	, m_bRequestRender( false )
	, m_bRequestEnd( false )
	, m_cCriticalSection()
{
}

/**
 * @brief		描画リクエスト。
 * @param[in]	_bRequest	: trueならリクエストを行う。
 */
void CRenderThread::SetRequestRender( bool _bRequest )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	m_bRequestRender = _bRequest;
}

/**
 * @brief		描画リクエストがあるか。
 * @retval		bool	: 描画リクエストがあればtrue。
 */
bool CRenderThread::IsRequestRender()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	return m_bRequestRender;
}

/**
 * @brief		終了リクエスト。
 * @param[in]	_bRequest	: trueなら終了する。
 */
void CRenderThread::SetRequestEnd( bool _bRequest )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	m_bRequestEnd = _bRequest;
}

/**
 * @brief		終了リクエストがあるか。
 * @retval		bool	: 終了リクエストがあればtrue。
 */
bool CRenderThread::IsRequestEnd()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	return m_bRequestEnd;
}


/**
 * @brief		描画コンテキストを取得。
 * @retval		IRenderContext	: 描画コンテキスト。
 */
IRenderContext* CRenderThread::GetRenderContext()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );	// 必要ないが念のため。
	return m_pcRenderContext;
}

/**
 * @brief		スレッドからコールバックされる関数。
 */
void CRenderThread::ThreadCallback()
{
	/// ループ。
	while ( !IsRequestEnd() )
	{
		if (IsRequestRender())
		{
			IRenderContext* pcContext = GetRenderContext();
			pcContext->Clear();

			CDrawList* pcDrawList = CDrawList::GetInstance();
			ASSERT( pcDrawList );
			if (pcDrawList)
			{
				pcDrawList->AllDraw( pcContext );
			}

			pcContext->Render();

			SetRequestRender( false );
		}
		else
		{
			std::this_thread::sleep_for( std::chrono::nanoseconds( 100 ) );
		}
	}
}

#endif 
