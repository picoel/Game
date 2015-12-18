/**
  * @file	PixelShader.cpp
  * @brief	DirectX11用ピクセルシェーダークラス。
  * @date 2015/07/06 01:42:38
  */

#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/PixelShader.h"
#include "Lib/DirectX/DirectX.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_rstInitParam	: 初期化用パラメータ。
 */
CPixelShader::CPixelShader( const StInitParam& _rstInitParam )
	: CFileReader( _rstInitParam.m_psFileName)
	, m_pcPixelShader( nullptr )
{
}

/**
 * @brief	デストラクタ。
 */
CPixelShader::~CPixelShader()
{
	SAFE_RELEASE( m_pcPixelShader );
}

/**
 * @brief		読み込み完了時の処理。
 * @param[in]	_pData	: 読み込んだデータ。
 * @param[in]	_uSize	: 読み込んだデータサイズ。
 */
void CPixelShader::ReadEndProcess( const void* _pData, USize _uSize )
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
		return;	 // failsafe
	}

	ASSERT( nullptr == m_pcPixelShader );
	SAFE_RELEASE( m_pcPixelShader );
	const HRESULT hResult = pcDevice->CreatePixelShader( _pData, _uSize, nullptr, &m_pcPixelShader );

	if (FAILED( hResult))
	{
		ASSERT( !"Failed CreatePixelShader" );
		return;	// failsafe
	}
}
