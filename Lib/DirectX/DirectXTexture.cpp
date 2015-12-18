/**
  * @file	DirectXTexture.cpp
  * @brief	DirectX�p�e�N�X�`���N���X�B
  * @date	2015/08/09 02:10:29
  */
#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/DirectX.h"
#include "Lib/DirectX/DirectXTexture.h"
#include "Lib/DirectX/DirectXUtility.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CDirectXTexture::CDirectXTexture()
	: m_pcTexture( nullptr )
	, m_pcResourceView( nullptr )
	, m_bIsCreate( false )
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CDirectXTexture::~CDirectXTexture()
{
	SAFE_RELEASE( m_pcTexture );
	SAFE_RELEASE( m_pcResourceView );
}

/**
 * @brief		�e�N�X�`�����쐬�B
 * @param[in]	_rstDesc	: �������B
 */
void CDirectXTexture::CreateTexture( const D3D_TEXTURE2D_DESC& _rstDesc )
{
	auto* pcDevice = CDirectX::GetDevice();
	ASSERT( pcDevice );
	if (nullptr == pcDevice)
	{
		return;
	}

	ASSERT( nullptr == m_pcTexture );
	SAFE_RELEASE( m_pcTexture );
	pcDevice->CreateTexture2D( &_rstDesc, nullptr, &m_pcTexture );

	D3D_SHADER_RESOURCE_VIEW_DESC stViewDesc;
	MemClear( &stViewDesc, sizeof( stViewDesc ) );
	stViewDesc.Format = _rstDesc.Format;
	stViewDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	stViewDesc.Texture2D.MipLevels = _rstDesc.MipLevels;
	stViewDesc.Texture2D.MostDetailedMip = 0;
	
	pcDevice->CreateShaderResourceView( m_pcTexture, &stViewDesc, &m_pcResourceView );

	m_bIsCreate = true;
}

/**
 * @brief		�e�N�X�`�����쐬�B
 * @param[in]	_rstImage		: �摜�f�[�^�B
 * @param[in]	_rstMetaData	: ���^�f�[�^�B
 */
void CDirectXTexture::CreateTexture( const DirectX::ScratchImage& _rstImage, const DirectX::TexMetadata& _rstMetaData )
{
	auto* pcDevice = CDirectX::GetDevice();
	ASSERT( pcDevice );
	if (nullptr == pcDevice)
	{
		return;	// failsafe
	}

	ID3DResource* pcResource = nullptr;
	const HRESULT hResultCreate = DirectX::CreateTexture( pcDevice, _rstImage.GetImages(), _rstImage.GetImageCount(), _rstMetaData, &pcResource );
	ASSERT( SUCCEEDED( hResultCreate ) );
	if (FAILED( hResultCreate ))
	{
		return;	// failsafe
	}
	m_pcTexture = s_cast<ID3DTexture2D*>( pcResource );

	D3D_SHADER_RESOURCE_VIEW_DESC stViewDesc;
	MemClear( &stViewDesc, sizeof( stViewDesc ) );
	stViewDesc.Format = _rstMetaData.format;
	stViewDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	stViewDesc.Texture2D.MipLevels = _rstMetaData.mipLevels;
	stViewDesc.Texture2D.MostDetailedMip = 0;

	pcDevice->CreateShaderResourceView( m_pcTexture, &stViewDesc, &m_pcResourceView );

	m_bIsCreate = true;
}

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_psFileName	: �ǂݍ��ރt�@�C�����B
 */
CDirectXTextureReader::CDirectXTextureReader( const TChar* _psFileName )
	: CFileReader( _psFileName )
	, m_eFormat( nLib::nDirectX::EnTextureFormat::enUnknown )
	, m_stImage()
	, m_stMetaData()
{
	m_eFormat = nLib::nDirectX::GetFormatFromFileName( _psFileName );
}

CDirectXTextureReader::CDirectXTextureReader( const TChar* _psFileName, nLib::nDirectX::EnTextureFormat _eFormat )
	: CFileReader( _psFileName)
	, m_eFormat( _eFormat )
	, m_stImage()
	, m_stMetaData()
{
}

/**
 * @brief		�ǂݍ��݊������̏����B
 * @param[in]	_pData	: �ǂݍ��񂾃f�[�^�B
 * @param[in]	_uSize	: �ǂݍ��񂾃f�[�^�̃T�C�Y�B
 */
void CDirectXTextureReader::ReadEndProcess( const void* _pData, USize _uSize )
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
		return;	// failsafe
	}

	const HRESULT hResultCoInit = CoInitializeEx( nullptr, COINIT_MULTITHREADED );
	if (FAILED( hResultCoInit ))
	{
		return;	// failsafe
	}

	switch (m_eFormat)
	{
	case nLib::nDirectX::EnTextureFormat::enDDS:
		{
			const HRESULT hResultLoad = DirectX::LoadFromDDSMemory( _pData, _uSize, 0, &m_stMetaData, m_stImage );
			if (FAILED( hResultLoad ))
			{
				return;	//failsafe
			}
			break;
		}

	case nLib::nDirectX::EnTextureFormat::enTGA:
		{
			const HRESULT hResultLoad = DirectX::LoadFromTGAMemory( _pData, _uSize, &m_stMetaData, m_stImage );
			if (FAILED( hResultLoad ))
			{
				return;	//failsafe
			}
			break;
		}

	case nLib::nDirectX::EnTextureFormat::enWIC:
		{
			const HRESULT hResultLoad = DirectX::LoadFromWICMemory( _pData, _uSize, 0, &m_stMetaData, m_stImage );
			if (FAILED( hResultLoad ))
			{
				return;	//failsafe
			}
			break;
		}
	}
	Log( "ReadTexture %s(%lldx%lld)[%lldbyte]", GetFileName(), m_stMetaData.width, m_stMetaData.height, _uSize );

	CoUninitialize();
}

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_pcTexture	: �e�N�X�`���쐬��B
 * @param[in]	_psFileName	: �摜�t�@�C�����B
 * @param[in]	_bIsSuicide	: �쐬�㎩�E���邩�ǂ����B
 */
CDirectXTextureCreatorFromFile::CDirectXTextureCreatorFromFile( CDirectXTexture* _pcTexture, const TChar* _psFileName, bool _bIsSuicide )
	: CDirectXTextureReader( _psFileName )
	, m_pcTexture( _pcTexture )
	, m_bIsSuicide( _bIsSuicide )
{
}

/**
 * @brief		�ǂݍ��݊������̏����B
 * @param[in]	_pData	: �ǂݍ��񂾃f�[�^�B
 * @param[in]	_uSize	: �ǂݍ��񂾃f�[�^�̃T�C�Y�B
 */
void CDirectXTextureCreatorFromFile::ReadEndProcess( const void* _pData, USize _uSize )
{
	CDirectXTextureReader::ReadEndProcess( _pData, _uSize );

	ASSERT( m_pcTexture );
	if (nullptr == m_pcTexture)
	{
		return;	// failsafe
	}

	m_pcTexture->CreateTexture( GetImage(), GetMetadata() );
}

/**
 * @brief		�ǂݍ��݊������̏���(���C���X���b�h�Ɠ����B)
 */
void CDirectXTextureCreatorFromFile::ReadEndProcessSync()
{
	if (m_bIsSuicide)
	{
		delete this;
	}
}
