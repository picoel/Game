/**
  * @file	RenderThread.h
  * @brief	描画用スレッド。
  * @date 2015/05/24 05:14:35
  */

#ifndef INCLUDE_LIB_RENDER_RENDERTHREAD_H
#define INCLUDE_LIB_RENDER_RENDERTHREAD_H

#include "Lib/Thread/Thread.h"
#include "Lib/Thread/CriticalSection.h"

class IRenderContext;
/*
 * @class CRenderThread
 * @brief 描画用スレッド。
 */
class CRenderThread : public CThread
{
public:
	/// コンストラクタ。
	CRenderThread( IRenderContext* _pcRenderContext );
	/// デストラクタ。
	~CRenderThread(){}

	/// 描画リクエスト。
	void SetRequestRender( bool _bRequest );
	/// 描画リクエストがあるか。
	bool IsRequestRender();

	/// 終了リクエスト。
	void SetRequestEnd( bool _bEnd );
	/// 終了リクエストがあるか。
	bool IsRequestEnd();

	/// 描画コンテキストを取得。
	IRenderContext* GetRenderContext();

	/// スレッドからコールバックされる関数。
	virtual void ThreadCallback() final;

private:
	IRenderContext*		m_pcRenderContext;
	bool				m_bRequestRender;
	bool				m_bRequestEnd;

	CCriticalSection	m_cCriticalSection;
};

#endif // #ifndef INCLUDE_LIB_RENDER_RENDERTHREAD_H