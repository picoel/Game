/**
  * @file	ConstantBuffer.cpp
  * @brief	�R���X�^���g�o�b�t�@�B
  * @data 2015/12/10 04:22:47
  */
#include "Lib/LibPrecompile.h"
#include "Lib/DirectX/ConstantBuffer.h"
#include "Lib/DirectX/DirectX.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_rcData	: �R���X�^���g�o�b�t�@�f�[�^�B
 */
CConstantBuffer::CConstantBuffer( const IConstantBufferData& _rcData )
	: m_pcBuffer( nullptr )
{
	CreateBuffer( _rcData );
}

/**
 * @brief		�f�X�g���N�^�B
 */
CConstantBuffer::~CConstantBuffer()
{
	SAFE_RELEASE( m_pcBuffer );
}

/**
 * @brief		�o�b�t�@���쐬�B
 * @param[in]	_rcData	: �R���X�^���g�o�b�t�@�f�[�^�B
 */
void CConstantBuffer::CreateBuffer( const IConstantBufferData& _rcData )
{
	ID3DDevice* pcDevice = CDirectX::GetDevice();
	ASSERT( pcDevice );
	if (nullptr == pcDevice)
	{
		return;	// failsafe
	}

	D3D_BUFFER_DESC stDesc;
	MemClear( &stDesc, sizeof( stDesc ) );
	stDesc.Usage = D3D_USAGE_DYNAMIC;
	stDesc.BindFlags = D3D_BIND_CONSTANT_BUFFER;
	stDesc.CPUAccessFlags = D3D_CPU_ACCESS_WRITE;
	stDesc.MiscFlags = 0;
	stDesc.StructureByteStride = 0;
	stDesc.ByteWidth = _rcData.GetSize();

	D3D_SUBRESOURCE_DATA stSubResource;
	MemClear( &stSubResource, sizeof( stSubResource ) );
	stSubResource.pSysMem = _rcData.GetData();

	ASSERT( nullptr == m_pcBuffer );
	SAFE_RELEASE( m_pcBuffer );
	const HRESULT hResult = pcDevice->CreateBuffer( &stDesc, &stSubResource, &m_pcBuffer );
	ASSERT( SUCCEEDED( hResult ) );
}
