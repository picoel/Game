/**
  * @file	PixelShader.cpp
  * @brief	DirectX11�p�s�N�Z���V�F�[�_�[�N���X�B
  * @date 2015/07/06 01:42:38
  */

#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/PixelShader.h"
#include "Lib/DirectX/DirectX.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_rstInitParam	: �������p�p�����[�^�B
 */
CPixelShader::CPixelShader( const StInitParam& _rstInitParam )
	: CFileReader( _rstInitParam.m_psFileName)
	, m_pcPixelShader( nullptr )
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CPixelShader::~CPixelShader()
{
	SAFE_RELEASE( m_pcPixelShader );
}

/**
 * @brief		�ǂݍ��݊������̏����B
 * @param[in]	_pData	: �ǂݍ��񂾃f�[�^�B
 * @param[in]	_uSize	: �ǂݍ��񂾃f�[�^�T�C�Y�B
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
