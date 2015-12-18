/**
  * @file	RenderContextFactoryDX11.h
  * @brief	DX11�p�`��R���e�L�X�g�����N���X�B
  * @data 2015/11/15 19:38:38
  */

#ifndef INCLUDE_LIB_DIRECTX_RENDER_CONTEXT_FACTORY_DX11_H
#define INCLUDE_LIB_DIRECTX_RENDER_CONTEXT_FACTORY_DX11_H

#if defined( USE_DIRECTX_11 )

#include "Lib/DirectX/RenderContextDX11.h"
#include "Lib/Render/RenderContextFactory.h"

/*
 * @class	CRenderContextFactoryDX11
 * @brief	DX11�p�`��R���e�L�X�g�����N���X�B
 */
class CRenderContextFactoryDX11 : public IRenderContextFactory
{
public:
	/// �R���X�g���N�^�B
	CRenderContextFactoryDX11( const CRenderContextDX11::StInitParam& _rstInitParam )
		: m_stParam()
	{
		MemCopy( &m_stParam, &_rstInitParam, sizeof( m_stParam ) );
	}
	/// �f�X�g���N�^�B
	virtual ~CRenderContextFactoryDX11(){}

	/// �����B
	virtual IRenderContext* Create() override
	{
		return pnew CRenderContextDX11( m_stParam );
	}

private:
	CRenderContextDX11::StInitParam	m_stParam;
};

#endif // #if defined( USE_DIRECTX_11 )

#endif // #ifndef INCLUDE_LIB_DIRECTX_RENDER_CONTEXT_FACTORY_DX11_H

