/**
  * @file	RenderThread.h
  * @brief	�`��p�X���b�h�B
  * @date 2015/05/24 05:14:35
  */

#ifndef INCLUDE_LIB_RENDER_RENDERTHREAD_H
#define INCLUDE_LIB_RENDER_RENDERTHREAD_H

#include "Lib/Thread/Thread.h"
#include "Lib/Thread/CriticalSection.h"

class IRenderContext;
/*
 * @class CRenderThread
 * @brief �`��p�X���b�h�B
 */
class CRenderThread : public CThread
{
public:
	/// �R���X�g���N�^�B
	CRenderThread( IRenderContext* _pcRenderContext );
	/// �f�X�g���N�^�B
	~CRenderThread(){}

	/// �`�惊�N�G�X�g�B
	void SetRequestRender( bool _bRequest );
	/// �`�惊�N�G�X�g�����邩�B
	bool IsRequestRender();

	/// �I�����N�G�X�g�B
	void SetRequestEnd( bool _bEnd );
	/// �I�����N�G�X�g�����邩�B
	bool IsRequestEnd();

	/// �`��R���e�L�X�g���擾�B
	IRenderContext* GetRenderContext();

	/// �X���b�h����R�[���o�b�N�����֐��B
	virtual void ThreadCallback() final;

private:
	IRenderContext*		m_pcRenderContext;
	bool				m_bRequestRender;
	bool				m_bRequestEnd;

	CCriticalSection	m_cCriticalSection;
};

#endif // #ifndef INCLUDE_LIB_RENDER_RENDERTHREAD_H