/**
  * @file	RenderContextDX11.h
  * @brief	DirectX11 描画コンテキスト。
  * @date 2015/05/21 06:18:57
  */

#ifndef INCLUDE_RENDER_CONTEXT_DX11_H
#define INCLUDE_RENDER_CONTEXT_DX11_H

#if defined( USE_DIRECTX_11 )

#include "Lib/Render/RenderContext.h"
#include "Lib/Thread/CriticalSection.h"

class CVertexShader;
class CPixelShader;
class CDirectXTexture;
class CDirectXShaderManager;

/*
 * @class CRenderContextDX11
 * @brief DirectX11 描画コンテキスト。
 */
class CRenderContextDX11 : public  IRenderContext
{
public:
	struct StInitParam
	{
		HWND	m_hWnd;
		U32		m_uWidth;
		U32		m_uHeight;

		void Init()
		{
			m_hWnd = NULL;
			m_uWidth = 0;
			m_uHeight = 0;
		}
	};

public:
	/// コンストラクタ。
	CRenderContextDX11( const StInitParam& _rstInitParam );
	/// デストラクタ。
	virtual ~CRenderContextDX11();

	/// 描画。
	virtual void Render() final;
	/// 画面のクリア。
	virtual void Clear() final;

	/// ポリゴンの描画。
	virtual void DrawIndexed( U32 _uIndexNum, U32 _uOffset ) override final;

	/// 使用可能かどうか。
	virtual bool IsEnabled() const override final;

	/// コンスタントバッファの更新。
	virtual void UpdateConstantBuffer( void* _pcBuffer, const IConstantBufferData& _rcData );
	/// コンスタントバッファーの設定。
	virtual void SetConstantBuffer( EnConstantBuffer _eKind, void* _pcBuffer ) override final;
	
	/// 頂点バッファの設定。
	virtual void SetVertexBuffer( U32 _uSlot, void* _pcBuffer, U32 _uStride, U32 _uOffset ) override final;
	/// インデックスバッファの設定。
	virtual void SetIndexBuffer( void* _pcBuffer, U32 _uOffset ) override final;
	/// プリミティブトポロジーを設定。
	virtual void SetPrimitiveTopology( U32 _uPrimitive ) override final;

	/// テクスチャを設定。
	virtual void SetTexture( U32 _uSlot, void* _pcTexture ) override final;

	/// 頂点シェーダーの設定。
	virtual void SetVertexShader( EnVertexShader _eShader ) override final;
	/// ピクセルシェーダーの設定。
	virtual void SetPixelShader( EnPixelShader _eShader ) override final;

private:
	/// 初期化。
	bool Init();

	/// DirectXの初期化	: スワップチェインの作成。
	bool InitDirectX_CreateSwapChain();
	/// DirectXの初期化 : レンダーターゲットの生成。
	bool InitDirectX_CreateRenderTargetView();
	/// DirectXの初期化 : Zバッファの作成。
	bool InitDirectX_CreateZBuffer();
	/// DirectXの初期化 : ビューポートの設定。
	bool InitDirectX_SetupViewPort();

private:
	StInitParam		m_stInitParam;

	ID3D11Device*				m_pcDevice;				///< DirectX11デバイス。
	ID3D11DeviceContext*		m_pcContext;			///< DirectX11描画コンテキスト。
	IDXGISwapChain*				m_pcSwapChain;			///< バックバッファの制御。
	ID3D11Texture2D*			m_pcBackBuffer;			///< バックバッファ。
	ID3D11RenderTargetView*		m_pcRenderTargetView;	///< レンダーターゲット。
	ID3D11DepthStencilView*		m_pcDepthStencilView;	///< 深度ステンシルビュー。
	ID3D11Texture2D*			m_pcDepthStencilBuffer;	///< 深度ステンシルバッファ。
	D3D_FEATURE_LEVEL			m_eFeatureLevel;		///< 機能レベル。

	CCriticalSection			m_cCriticalSection;		///< クリティカルセクション。

	CDirectXShaderManager*		m_pcShaderManager;		///< シェーダー管理。
};

#endif // #if defined( USE_DIRECTX_11 )

#endif // #ifndef INCLUDE_RENDER_CONTEXT_DX11_H