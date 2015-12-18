/**
  * @file	ConstantBuffer.cpp
  * @brief	コンスタントバッファ。
  * @data 2015/12/10 04:22:47
  */
#include "Lib/LibPrecompile.h"
#include "Lib/DirectX/ConstantBuffer.h"
#include "Lib/DirectX/DirectX.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_rcData	: コンスタントバッファデータ。
 */
CConstantBuffer::CConstantBuffer( const IConstantBufferData& _rcData )
	: m_pcBuffer( nullptr )
{
	CreateBuffer( _rcData );
}

/**
 * @brief		デストラクタ。
 */
CConstantBuffer::~CConstantBuffer()
{
	SAFE_RELEASE( m_pcBuffer );
}

/**
 * @brief		バッファを作成。
 * @param[in]	_rcData	: コンスタントバッファデータ。
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
