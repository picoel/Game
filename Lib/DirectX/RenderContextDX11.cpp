/**
  * @file	RenderContextDX11.cpp
  * @brief	DirectX11 描画コンテキスト。
  * @date 2015/05/21 06:18:57
  */

#include "Lib/LibPrecompile.h"

#if defined( USE_DIRECTX_11 )

#include "Lib/DirectX/DirectX.h"
#include "Lib/DirectX/DirectXTexture.h"
#include "Lib/DirectX/RenderContextDX11.h"
#include "Lib/DirectX/VertexShader.h"
#include "Lib/DirectX/PixelShader.h"
#include "Lib/DirectX/DirectXShaderManager.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_rstInitParam	: 初期化用パラメータ。
 */
CRenderContextDX11::CRenderContextDX11( const StInitParam& _rstInitParam )
	: IRenderContext()
	, m_stInitParam()
	, m_pcDevice( nullptr )
	, m_pcContext( nullptr )
	, m_pcSwapChain( nullptr )
	, m_pcBackBuffer( nullptr )
	, m_pcRenderTargetView( nullptr )
	, m_pcDepthStencilView( nullptr )
	, m_pcDepthStencilBuffer( nullptr )
	, m_eFeatureLevel( D3D_FEATURE_LEVEL_11_1 )
	, m_cCriticalSection()
	, m_pcShaderManager( nullptr )
{
	MemCopy( &m_stInitParam, &_rstInitParam, sizeof( m_stInitParam ) );
	Init();
}

/**
 * @brief	デストラクタ。
 */
CRenderContextDX11::~CRenderContextDX11()
{
	P_DELETE( m_pcShaderManager );

	SAFE_RELEASE( m_pcDepthStencilBuffer );
	SAFE_RELEASE( m_pcDepthStencilView );
	SAFE_RELEASE( m_pcRenderTargetView );
	SAFE_RELEASE( m_pcBackBuffer );
	SAFE_RELEASE( m_pcSwapChain );
	SAFE_RELEASE( m_pcContext );
	SAFE_RELEASE( m_pcDevice );
}

/**
 * @brief	描画。
 */
void CRenderContextDX11::Render()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	ASSERT( m_pcSwapChain );
	if (nullptr == m_pcSwapChain)
	{
		return;	// failsafe
	}

	m_pcSwapChain->Present( 1, 0 );
}

/**
 * @brief	画面のクリア。
 */
void CRenderContextDX11::Clear()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return; // failsafe
	}

	ASSERT( m_pcRenderTargetView );
	if (nullptr == m_pcRenderTargetView)
	{
		return; // failsafe
	}

	ASSERT( m_pcDepthStencilView );
	if (nullptr == m_pcDepthStencilView)
	{
		return; // failsafe
	}

	const F32 fColorAry[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_pcContext->ClearRenderTargetView( m_pcRenderTargetView, fColorAry );
	m_pcContext->ClearDepthStencilView( m_pcDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
}

/**
 * @brief		ポリゴンを描画。
 * @param[in]	_uIndexNum	: 描画するインデックス数。
 * @param[in]	_uOffset	: オフセット値。
 */
void CRenderContextDX11::DrawIndexed( U32 _uIndexNum, U32 _uOffset )
{
	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return; // failsafe
	}

	m_pcContext->DrawIndexed( _uIndexNum, _uOffset, 0 );
}

/**
 * @brief		使用可能かどうか。
 * @retval		bool	: 使用可能ならtrue。
 */
bool CRenderContextDX11::IsEnabled() const
{
	bool bRet = false;

	if (m_pcShaderManager)
	{
		if (m_pcShaderManager->IsReadEnd())
		{
			bRet = true;
		}
	}

	return bRet;
}

/**
 * @brief		コンスタントバッファの更新。
 * @param[in]	_pcBuffer	: 更新するバッファ。
 * @param[in]	_rcData		: データ。
 */
void CRenderContextDX11::UpdateConstantBuffer( void* _pcBuffer, const IConstantBufferData& _rcData )
{
	ASSERT( _pcBuffer );
	if (nullptr == _pcBuffer)
	{
		return;	// failsafe
	}

	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return;	// failsafe
	}

	m_pcContext->UpdateSubresource( s_cast<ID3DResource*>(_pcBuffer), 0, nullptr, _rcData.GetData(), 0, 0 );
}

/**
 * @brief		コンスタントバッファーの設定。
 * @param[in]	_eKind		: 設定するコンスタントバッファーの種類。
 * @param[in]	_pcBuffer	: 設定するデータ。
 */
void CRenderContextDX11::SetConstantBuffer( EnConstantBuffer _eKind, void* _pcBuffer )
{
	ASSERT( _pcBuffer );
	if (nullptr == _pcBuffer)
	{
		return;	// failsafe
	}

	ASSERT( _eKind < EnConstantBuffer::enMax );
	if (EnConstantBuffer::enMax <= _eKind)
	{
		return;	// failsafe
	}

	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return;	// failsafe
	}
	ID3DBuffer* pcD3DBuffer = s_cast<ID3DBuffer*>( _pcBuffer );
	m_pcContext->VSSetConstantBuffers( s_cast<U32>( _eKind ), 1, &pcD3DBuffer );
	m_pcContext->PSSetConstantBuffers( s_cast<U32>( _eKind ), 1, &pcD3DBuffer );
}

/**
 * @brief		頂点バッファの設定。
 * @param[in]	_uSlot		: バッファを設定するスロット。
 * @param[in]	_pcBuffer	: セットするバッファ。
 * @param[in]	_uStride	: 頂点のサイズ。
 * @param[in]	_uOffset	: 先頭からのオフセット。
 */
void CRenderContextDX11::SetVertexBuffer( U32 _uSlot, void* _pcBuffer, U32 _uStride, U32 _uOffset )
{
	ASSERT( _pcBuffer );
	if (nullptr == _pcBuffer)
	{
		return;	// failsafe
	}

	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return;	// failsafe
	}

	ID3DBuffer* pcD3DBuffer = s_cast<ID3DBuffer*>( _pcBuffer );
	m_pcContext->IASetVertexBuffers( _uSlot, 1, &pcD3DBuffer, &_uStride, &_uOffset );
}

/**
 * @brief		インデックスバッファの設定。
 * @param[in]	_pcBuffer	: セットするバッファ。
 * @param[in]	_uOffset	: 先頭からのオフセット。
 */
void CRenderContextDX11::SetIndexBuffer( void* _pcBuffer, U32 _uOffset )
{
	ASSERT( _pcBuffer );
	if (nullptr == _pcBuffer)
	{
		return;	// failsafe
	}

	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return;	// failsafe
	}

	ID3DBuffer* pcD3DBuffer = s_cast<ID3DBuffer*>( _pcBuffer );
	m_pcContext->IASetIndexBuffer( pcD3DBuffer, DXGI_FORMAT_R32_UINT, _uOffset );
}

/**
 * @brief		プリミティブトポロジーの設定。
 * @param[in]	_uPrimitive	: プリミティブトポロジー。
 */
void CRenderContextDX11::SetPrimitiveTopology( U32 _uPrimitive )
{
	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return;	 // failsafe
	}

	m_pcContext->IASetPrimitiveTopology( s_cast<D3D11_PRIMITIVE_TOPOLOGY>(_uPrimitive) );
}

/**
 * @brief		テクスチャを設定。
 * @param[in]	_uSlot		: 設定するスロット。
 * @param[in]	_pcTexture	: テクスチャ。
 */
void CRenderContextDX11::SetTexture( U32 _uSlot, void* _pcTexture )
{
}


/**
 * @brief		頂点シェーダーの設定。
 * @param[in]	_eShader	: 設定する頂点シェーダー。
 */
void CRenderContextDX11::SetVertexShader( EnVertexShader _eShader )
{
	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return;	// failsafe
	}

	ASSERT( m_pcShaderManager );
	if (nullptr == m_pcShaderManager)
	{
		return;	// failsafe
	}

	const CVertexShader* pcShader = m_pcShaderManager->GetVertexShader( _eShader );
	ASSERT( pcShader );
	if (nullptr == pcShader)
	{
		return;	// failsafe
	}

	m_pcContext->VSSetShader( pcShader->GetShader(), nullptr, 0 );
	m_pcContext->IASetInputLayout( pcShader->GetInputLayout() );		//#TODO: ここじゃないほうがいい。
}

/**
 * @brief		ピクセルシェーダーの設定。
 * @param[in]	_eShader	: 設定するピクセルシェーダー。
 */
void CRenderContextDX11::SetPixelShader( EnPixelShader _eShader )
{
	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return;	// failsafe
	}

	ASSERT( m_pcShaderManager );
	if (nullptr == m_pcShaderManager)
	{
		return;	// failsafe
	}

	const CPixelShader* pcShader = m_pcShaderManager->GetPixelShader( _eShader );
	ASSERT( pcShader );
	if (nullptr == pcShader)
	{
		return;	// failsafe
	}

	m_pcContext->PSSetShader( pcShader->GetShader(), nullptr, 0 );
}

/**
 * @brief		初期化。
 * @return		bool	: 成功したらtrue。
 */
bool CRenderContextDX11::Init()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	ASSERT( nullptr == m_pcDevice );
	SAFE_RELEASE( m_pcDevice );
	m_pcDevice = CDirectX::GetDevice();

	ASSERT( m_pcDevice );
	if (nullptr == m_pcDevice)
	{
		return false;
	}

	m_pcDevice->AddRef();

	ASSERT( nullptr == m_pcContext );
	SAFE_RELEASE( m_pcContext );
	m_pcDevice->GetImmediateContext( &m_pcContext );

	if (!InitDirectX_CreateSwapChain())
	{
		ASSERT( !"Failed CreateDevice()" );
		return false;
	}

	if (!InitDirectX_CreateRenderTargetView())
	{
		ASSERT( !"Failed CreateRenderTargetView()" );
		return false;
	}

	if (!InitDirectX_CreateZBuffer())
	{
		ASSERT( !"Failed CreateZBuffer" );
		return false;
	}

	ASSERT( nullptr == m_pcShaderManager );
	P_DELETE( m_pcShaderManager );
	m_pcShaderManager = pnew CDirectXShaderManager();

	return true;
}

/**
 * @brief	DirectXの初期化 : スワップチェインの作成。
 * @retval	bool	: 成功したらtrue。
 * @note	InitDirectX()から呼ばれます。
 */
bool CRenderContextDX11::InitDirectX_CreateSwapChain()
{
	IDXGIDevice* pDxgiDevice = nullptr;
	const HRESULT hResultQuery = m_pcDevice->QueryInterface( &pDxgiDevice );
	ASSERT( SUCCEEDED( hResultQuery ) );
	if (FAILED( hResultQuery ))
	{
		return false;	// failsafe
	}

	IDXGIAdapter* pDxgiAdapter = nullptr;
	const HRESULT hResultAdapter = pDxgiDevice->GetAdapter( &pDxgiAdapter );
	SAFE_RELEASE( pDxgiDevice );
	ASSERT( SUCCEEDED( hResultAdapter ) );
	if (FAILED( hResultAdapter ))
	{
		return false;	// failsafe
	}

	IDXGIFactory* pDxgiFactory = nullptr;
	const HRESULT hResultFactory = pDxgiAdapter->GetParent( __uuidof( IDXGIFactory ), r_cast<void**>(&pDxgiFactory) );
	SAFE_RELEASE( pDxgiAdapter );
	ASSERT( SUCCEEDED( hResultFactory ) );
	if (FAILED( hResultFactory ))
	{
		return false;	// failsafe
	}

	DXGI_SWAP_CHAIN_DESC stSwapChainDesc;
	MemClear( &stSwapChainDesc, sizeof( stSwapChainDesc ) );
	stSwapChainDesc.BufferCount = 1;
	stSwapChainDesc.BufferDesc.Width = m_stInitParam.m_uWidth;
	stSwapChainDesc.BufferDesc.Height = m_stInitParam.m_uHeight;
	stSwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	stSwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	stSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	stSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	stSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	stSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	stSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	stSwapChainDesc.OutputWindow = m_stInitParam.m_hWnd;
	stSwapChainDesc.SampleDesc.Count = 1;
	stSwapChainDesc.SampleDesc.Quality = 0;
	stSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	stSwapChainDesc.Windowed = TRUE;

	ASSERT( nullptr == m_pcSwapChain );
	SAFE_RELEASE( m_pcSwapChain );
	const HRESULT hResult = pDxgiFactory->CreateSwapChain(
		m_pcDevice,
		&stSwapChainDesc,
		&m_pcSwapChain
		);

	bool bRet = false;
	if (SUCCEEDED( hResult ))
	{
		bRet = true;
	}

	SAFE_RELEASE( pDxgiFactory );
	return bRet;
}

/**
 * @brief	DirectXの初期化 : レンダーターゲットの生成。
 * @retval	bool	: 成功したらtrue。
 * @note	InitDirectX()から呼ばれます。
 */
bool CRenderContextDX11::InitDirectX_CreateRenderTargetView()
{
	ASSERT( m_pcDevice );
	if (nullptr == m_pcDevice)
	{
		return false;	// failsafe
	}

	ASSERT( m_pcSwapChain );
	if (nullptr == m_pcSwapChain)
	{
		return false;	// failsafe
	}

	HRESULT hResult = m_pcSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), r_cast<void**>(&m_pcBackBuffer) );
	if (FAILED( hResult ))
	{
		return false;
	}

	hResult = m_pcDevice->CreateRenderTargetView( m_pcBackBuffer, nullptr, &m_pcRenderTargetView );
	if (FAILED( hResult ))
	{
		return false;
	}

	return true;
}

/**
 * @brief	DirectXの初期化 : Zバッファの作成。
 * @retval	bool	: 成功したらtrue。
 * @note	InitDirectX()から呼ばれます。
 */
bool CRenderContextDX11::InitDirectX_CreateZBuffer()
{
	ASSERT( m_pcDevice );
	if (nullptr == m_pcDevice)
	{
		return false; // failsafe
	}

	ASSERT( m_pcRenderTargetView );
	if (nullptr == m_pcRenderTargetView)
	{
		return false; // failsafe
	}

	D3D11_TEXTURE2D_DESC stDescTex2D;
	MemClear( &stDescTex2D, sizeof( stDescTex2D ) );
	stDescTex2D.Width = m_stInitParam.m_uWidth;
	stDescTex2D.Height = m_stInitParam.m_uHeight;
	stDescTex2D.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	stDescTex2D.MipLevels = 1;
	stDescTex2D.ArraySize = 1;
	stDescTex2D.SampleDesc.Count = 1;
	stDescTex2D.SampleDesc.Quality = 0;
	stDescTex2D.Usage = D3D11_USAGE_DEFAULT;
	stDescTex2D.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	HRESULT hResult = m_pcDevice->CreateTexture2D( &stDescTex2D, nullptr, &m_pcDepthStencilBuffer );
	if (FAILED( hResult ))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC stDescDepthStencilView;
	MemClear( &stDescDepthStencilView, sizeof( stDescDepthStencilView ) );
	stDescDepthStencilView.Format = stDescTex2D.Format;
	stDescDepthStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	stDescDepthStencilView.Texture2D.MipSlice = 0;

	hResult = m_pcDevice->CreateDepthStencilView( m_pcDepthStencilBuffer, &stDescDepthStencilView, &m_pcDepthStencilView );
	if (FAILED( hResult ))
	{
		return false;
	}

	m_pcContext->OMSetRenderTargets( 1, &m_pcRenderTargetView, m_pcDepthStencilView );

	return true;
}

/**
 * @brief	DirectXの初期化 : ビューポートの設定。
 * @retval	bool	: 成功したらtrue。
 * @note	InitDirectX()から呼ばれます。
 */
bool CRenderContextDX11::InitDirectX_SetupViewPort()
{
	ASSERT( m_pcContext );
	if (nullptr == m_pcContext)
	{
		return false; // failsafe
	}

	D3D11_VIEWPORT stViewPort;
	MemClear( &stViewPort, sizeof( stViewPort ) );
	stViewPort.TopLeftX = 0;
	stViewPort.TopLeftY = 0;
	stViewPort.Width = s_cast<F32>(m_stInitParam.m_uWidth);
	stViewPort.Height = s_cast<F32>(m_stInitParam.m_uHeight);
	stViewPort.MinDepth = 0.0f;
	stViewPort.MaxDepth = 1.0f;

	m_pcContext->RSSetViewports( 1, &stViewPort );
	return true;
}

#endif // #if defined( USE_DIRECTX_11 )
