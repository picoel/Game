/**
  * @file	RenderThread.cpp
  * @brief	�`��p�X���b�h�B
  * @date 2015/05/24 05:14:35
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Render/RenderThread.h"
#include "Lib/Render/RenderContext.h"

#include "Lib/Object/DrawList.h"

#if 0

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_pcRenderContext	: �`��R���e�L�X�g�B
 */
CRenderThread::CRenderThread( IRenderContext* _pcRenderContext )
	: m_pcRenderContext( _pcRenderContext )
	, m_bRequestRender( false )
	, m_bRequestEnd( false )
	, m_cCriticalSection()
{
}

/**
 * @brief		�`�惊�N�G�X�g�B
 * @param[in]	_bRequest	: true�Ȃ烊�N�G�X�g���s���B
 */
void CRenderThread::SetRequestRender( bool _bRequest )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	m_bRequestRender = _bRequest;
}

/**
 * @brief		�`�惊�N�G�X�g�����邩�B
 * @retval		bool	: �`�惊�N�G�X�g�������true�B
 */
bool CRenderThread::IsRequestRender()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	return m_bRequestRender;
}

/**
 * @brief		�I�����N�G�X�g�B
 * @param[in]	_bRequest	: true�Ȃ�I������B
 */
void CRenderThread::SetRequestEnd( bool _bRequest )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	m_bRequestEnd = _bRequest;
}

/**
 * @brief		�I�����N�G�X�g�����邩�B
 * @retval		bool	: �I�����N�G�X�g�������true�B
 */
bool CRenderThread::IsRequestEnd()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	return m_bRequestEnd;
}


/**
 * @brief		�`��R���e�L�X�g���擾�B
 * @retval		IRenderContext	: �`��R���e�L�X�g�B
 */
IRenderContext* CRenderThread::GetRenderContext()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );	// �K�v�Ȃ����O�̂��߁B
	return m_pcRenderContext;
}

/**
 * @brief		�X���b�h����R�[���o�b�N�����֐��B
 */
void CRenderThread::ThreadCallback()
{
	/// ���[�v�B
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
