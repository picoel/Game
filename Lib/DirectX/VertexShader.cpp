/**
  * @file	VertexShader.h
  * @brief	頂点シェーダークラス。
  * @date 2015/07/05 03:57:34
  */

#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/VertexShader.h"
#include "Lib/DirectX/DirectX.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_rstInitParam	: 初期化用パラメータ。
 */
CVertexShader::CVertexShader( const StInitParam& _rstInitParam )
	: CFileReader( _rstInitParam.m_psFileName )
	, m_pcVertexShader( nullptr )
	, m_pcInputLayout( nullptr )
{
}

/**
 * @brief	デストラクタ。
 */
CVertexShader::~CVertexShader()
{
	SAFE_RELEASE( m_pcVertexShader );
	SAFE_RELEASE( m_pcInputLayout );
}

/**
 * @brief		読み込み完了時の処理。
 * @param[in]	_pData	: 読み込んだデータ。
 * @param[in]	_uSize	: 読み込んだデータサイズ。
 */
void CVertexShader::ReadEndProcess( const void* _pData, USize _uSize )
{
	ASSERT( _pData );
	if (nullptr == _pData)
	{
		return;	// failsafe
	}

	auto* pcDevice = CDirectX::GetDevice();
	ASSERT( pcDevice );
	if (nullptr == pcDevice)
	{
		return; // failsafe
	}

	ASSERT( nullptr == m_pcVertexShader );
	SAFE_RELEASE( m_pcVertexShader );
	const HRESULT hResultVS = pcDevice->CreateVertexShader( _pData, _uSize, nullptr, &m_pcVertexShader );

	if (FAILED(hResultVS))
	{
		ASSERT( !"Failed CreateVertexShader" );
		return;	// failsafe
	}

	// コンパイル済みシェーダーから入力レイアウトを作成する。
	ID3DShaderReflection* pcShaderReflection = nullptr;
	const HRESULT hResultRefrect = D3DReflect( _pData, _uSize, IID_ID3DShaderReflection, r_cast<void**>( &pcShaderReflection ) );
	if (FAILED(hResultRefrect))
	{
		ASSERT( !"Failed CreateShaderReflection" );
		return; // failsafe
	}

	D3D_SHADER_DESC stShaderDesc;
	MemClear( &stShaderDesc, sizeof( stShaderDesc ) );
	const HRESULT hResult = pcShaderReflection->GetDesc( &stShaderDesc );
	if (FAILED( hResult ))
	{
		ASSERT(!"Failed ShaderReflection GetDesc")
		SAFE_RELEASE( pcShaderReflection );
		return;	// failsafe
	}

	ASSERT( 0 < stShaderDesc.InputParameters );
	if (stShaderDesc.InputParameters <= 0)
	{
		SAFE_RELEASE( pcShaderReflection );
		return;	// failsafe
	}

	D3D_INPUT_ELEMENT_DESC* pstInputDescArray = pnew D3D_INPUT_ELEMENT_DESC[ stShaderDesc.InputParameters ];
	for (U32 ii = 0; ii < stShaderDesc.InputParameters; ++ii)
	{
		D3D_SIGNATURE_PARAMETER_DESC stSignParamDesc;
		pcShaderReflection->GetInputParameterDesc( ii, &stSignParamDesc );
		auto eFormat = GetDxgiFormat( stSignParamDesc.ComponentType, stSignParamDesc.Mask );

		pstInputDescArray[ ii ].SemanticName = stSignParamDesc.SemanticName;
		pstInputDescArray[ ii ].SemanticIndex = stSignParamDesc.SemanticIndex;
		pstInputDescArray[ ii ].Format = eFormat;
		pstInputDescArray[ ii ].InputSlot = 0;
		pstInputDescArray[ ii ].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		pstInputDescArray[ ii ].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pstInputDescArray[ ii ].InstanceDataStepRate = 0;
	}

	ASSERT( nullptr == m_pcInputLayout );
	SAFE_RELEASE( m_pcInputLayout );
	const HRESULT hResultInputLayout = pcDevice->CreateInputLayout
		( pstInputDescArray, stShaderDesc.InputParameters, _pData, _uSize, &m_pcInputLayout );

	SAFE_RELEASE( pcShaderReflection );
	P_DELETE_ARRAY( pstInputDescArray );

	if (FAILED( hResultInputLayout ))
	{
		ASSERT( !"Failed CraeteInputLayout" );
		return;	// failsafe
	}
}

/**
 * @brief		DXGIフォーマットの取得。
 * @param[in]	_uType	: フォーマットタイプ。
 * @param[in]	_uMask	: マスク(xyzwを使用しているか。)
 * @note		floatにしか対応していません。他の型を使用する場合は処理を追加する必要があります。
 */
DXGI_FORMAT CVertexShader::GetDxgiFormat( D3D_REGISTER_COMPONENT_TYPE _uType, U32 _uMask )
{
	const U32 uUseXYZW = _uMask & 0x0F;

	DXGI_FORMAT eRet = DXGI_FORMAT_UNKNOWN;
	// xyzw
	if (0x0F == uUseXYZW)
	{
		switch (_uType)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			eRet = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;

		default:
			break;
		}
	}
	// xyz
	else if (0x07 == uUseXYZW)
	{
		switch (_uType)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			eRet = DXGI_FORMAT_R32G32B32_FLOAT;
			break;

		default:
			break;
		}
	}
	// xy
	else if (0x03 == uUseXYZW)
	{
		switch (_uType)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			eRet = DXGI_FORMAT_R32G32_FLOAT;
			break;

		default:
			break;
		}
	}
	// x
	else if (0x01 == uUseXYZW)
	{
		switch (_uType)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			eRet = DXGI_FORMAT_R32_FLOAT;
			break;

		default:
			break;
		}
	}

	return eRet;
}
