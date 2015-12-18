/**
  * @file	RenderContextFactoryDX11.h
  * @brief	DX11用描画コンテキスト生成クラス。
  * @data 2015/11/15 19:38:38
  */

#ifndef INCLUDE_LIB_DIRECTX_RENDER_CONTEXT_FACTORY_DX11_H
#define INCLUDE_LIB_DIRECTX_RENDER_CONTEXT_FACTORY_DX11_H

#if defined( USE_DIRECTX_11 )

#include "Lib/DirectX/RenderContextDX11.h"
#include "Lib/Render/RenderContextFactory.h"

/*
 * @class	CRenderContextFactoryDX11
 * @brief	DX11用描画コンテキスト生成クラス。
 */
class CRenderContextFactoryDX11 : public IRenderContextFactory
{
public:
	/// コンストラクタ。
	CRenderContextFactoryDX11( const CRenderContextDX11::StInitParam& _rstInitParam )
		: m_stParam()
	{
		MemCopy( &m_stParam, &_rstInitParam, sizeof( m_stParam ) );
	}
	/// デストラクタ。
	virtual ~CRenderContextFactoryDX11(){}

	/// 生成。
	virtual IRenderContext* Create() override
	{
		return pnew CRenderContextDX11( m_stParam );
	}

private:
	CRenderContextDX11::StInitParam	m_stParam;
};

#endif // #if defined( USE_DIRECTX_11 )

#endif // #ifndef INCLUDE_LIB_DIRECTX_RENDER_CONTEXT_FACTORY_DX11_H

