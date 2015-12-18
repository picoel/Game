/**
  * @file	MeshDrawer.cpp
  * @brief	���b�V���`��B
  * @data 2015/12/03 06:26:54
  */
#include "Lib/LibPrecompile.h"
#include "Lib/Mesh/MeshDrawer.h"
#include "Lib/DirectX/DirectX.h"
#include "Lib/DirectX/DirectXTexture.h"
#include "Lib/DirectX/ConstantBuffer.h"
#include "Lib/Render/RenderContext.h"
#include "Lib/Render/ConstantBufferDataForMaterial.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_pcMesh	: ���b�V�����B
 */
CMeshDrawer::CMeshDrawer( const IMesh* _pcMesh )
	: m_pcVertexBuffer( nullptr )
	, m_pcIndexBuffer( nullptr )
	, m_uMaterialNum( 0 )
	, m_pstMaterialArray( nullptr )
{
	ASSERT( _pcMesh );
	if (_pcMesh)
	{
		CreateVertexBuffer( _pcMesh );
		CreateIndexBuffer( _pcMesh );
		CreateMaterial( _pcMesh );
	}
}

/**
 * @brief		�f�X�g���N�^�B
 */
CMeshDrawer::~CMeshDrawer()
{
	SAFE_RELEASE( m_pcVertexBuffer );
	SAFE_RELEASE( m_pcIndexBuffer );

	if ( m_pstMaterialArray )
	{
		for (U32 ii = 0; ii < m_uMaterialNum; ++ii)
		{

			P_DELETE( m_pstMaterialArray[ ii ].m_pcConstantBuffer );
			P_DELETE( m_pstMaterialArray[ ii ].m_pcTexture );
		}
		P_DELETE_ARRAY( m_pstMaterialArray );
	}
}

/**
 * @brief		�`�揈���B
 * @param[in]	_pcContext	: �`��R���e�L�X�g�B
 */
void CMeshDrawer::Draw( IRenderContext* _pcContext )
{
	//#TODO �`�揈���̍쐬�B
	ASSERT( _pcContext );
	if (nullptr == _pcContext)
	{
		return;	// failsafe
	}

	ASSERT( m_pcVertexBuffer );
	if (nullptr == m_pcVertexBuffer)
	{
		return;	// failsafe
	}

	ASSERT( m_pcIndexBuffer );
	if (nullptr == m_pcIndexBuffer)
	{
		return;	// failsafe
	}

	ASSERT( m_pstMaterialArray );
	if (nullptr == m_pstMaterialArray)
	{
		return;	 // failsafe
	}

	_pcContext->SetVertexBuffer( 0, m_pcVertexBuffer, sizeof( IMesh::StVertex ), 0 );
	_pcContext->SetIndexBuffer( m_pcIndexBuffer, 0 );

	U32 uOffset = 0;
	for (U32 ii = 0; ii < m_uMaterialNum; ++ii)
	{
		_pcContext->SetTexture( 0, m_pstMaterialArray[ ii ].m_pcTexture );
		_pcContext->SetConstantBuffer( EnConstantBuffer::enMaterial, m_pstMaterialArray[ ii ].m_pcConstantBuffer->GetBuffer() );

		_pcContext->DrawIndexed( m_pstMaterialArray[ ii ].m_uVertexNum, uOffset );

		uOffset += m_pstMaterialArray[ ii ].m_uVertexNum;
	}
}

/**
 * @brief		�ǂݍ��݂������������B
 * @retval		bool	: �������Ă����true�B
 */
bool CMeshDrawer::IsReadEnd() const
{
	if (nullptr == m_pstMaterialArray)
	{
		return false;
	}

	bool bRet = true;
	for (U32 ii = 0; ii < m_uMaterialNum; ++ii)
	{
		if (m_pstMaterialArray[ ii ].m_pcTexture)
		{
			if (!m_pstMaterialArray[ ii ].m_pcTexture->IsCreate())
			{
				bRet = false;
				break;
			}
		}
	}

	return bRet;
}

/**
 * @brief		���_�o�b�t�@�[�̍쐬�B
 * @param[in]	_pcMesh	: ���b�V�����B
 */
void CMeshDrawer::CreateVertexBuffer( const IMesh* _pcMesh )
{
	ID3DDevice* pcDevice = CDirectX::GetDevice();
	ASSERT( pcDevice );
	if (nullptr == pcDevice)
	{
		return;	// failsafe
	}

	D3D_BUFFER_DESC	stDesc;
	MemClear( &stDesc, sizeof( stDesc ) );
	stDesc.Usage = D3D_USAGE_DEFAULT;
	stDesc.ByteWidth = sizeof( IMesh::StVertex ) * _pcMesh->GetVertexNum();
	stDesc.BindFlags = D3D_BIND_VERTEX_BUFFER;
	stDesc.CPUAccessFlags = 0;

	D3D_SUBRESOURCE_DATA stSubResource;
	MemClear( &stSubResource, sizeof( stSubResource ) );
	stSubResource.pSysMem = _pcMesh->GetVertexArray();

	ASSERT( nullptr == m_pcVertexBuffer );
	SAFE_RELEASE( m_pcVertexBuffer );
	const HRESULT hResult = pcDevice->CreateBuffer( &stDesc, &stSubResource, &m_pcVertexBuffer );
	
	ASSERT( SUCCEEDED( hResult ) );
}

/**
 * @brief		�C���f�b�N�X�o�b�t�@�[�̍쐬�B
 * @param[in]	_pcMesh	: ���b�V�����B
 */
void CMeshDrawer::CreateIndexBuffer( const IMesh* _pcMesh )
{
	ID3DDevice* pcDevice = CDirectX::GetDevice();
	ASSERT( pcDevice );
	if (nullptr == pcDevice)
	{
		return;	// failsafe
	}

	D3D_BUFFER_DESC	stDesc;
	MemClear( &stDesc, sizeof( stDesc ) );
	stDesc.Usage = D3D_USAGE_DEFAULT;
	stDesc.ByteWidth = sizeof( U32 ) * _pcMesh->GetIndexNum();
	stDesc.BindFlags = D3D_BIND_INDEX_BUFFER;
	stDesc.CPUAccessFlags = 0;

	D3D_SUBRESOURCE_DATA stSubResource;
	MemClear( &stSubResource, sizeof( stSubResource ) );
	stSubResource.pSysMem = _pcMesh->GetIndexArray();

	ASSERT( nullptr == m_pcIndexBuffer );
	SAFE_RELEASE( m_pcIndexBuffer );
	const HRESULT hResult = pcDevice->CreateBuffer( &stDesc, &stSubResource, &m_pcIndexBuffer );
	
	ASSERT( SUCCEEDED( hResult ) );
}

/**
 * @brief		�}�e���A�����̍쐬�B
 * @param[in]	_pcMesh	: ���b�V�����B
 */
void CMeshDrawer::CreateMaterial( const IMesh* _pcMesh )
{
	m_uMaterialNum = _pcMesh->GetMaterialNum();
	const IMesh::StMaterial* pstMaterialArray = _pcMesh->GetMaterialArray();
	ASSERT( pstMaterialArray );
	if ( nullptr == pstMaterialArray)
	{
		return;	// failsafe
	}

	ASSERT( nullptr == m_pstMaterialArray );
	P_DELETE_ARRAY( m_pstMaterialArray );
	m_pstMaterialArray = pnew StMaterial[ m_uMaterialNum ];

	for (U32 ii = 0; ii < m_uMaterialNum; ++ii)
	{
		m_pstMaterialArray[ ii ].m_uVertexNum = pstMaterialArray[ ii ].m_uVertexNum;

		CConstantBufferDataForMaterial cConstantBufferData;
		cConstantBufferData.SetDiffuse( pstMaterialArray[ ii ].m_stDiffuse );
		cConstantBufferData.SetAmbient( pstMaterialArray[ ii ].m_stAmbient );
		cConstantBufferData.SetSpecular( pstMaterialArray[ ii ].m_stSpecular );
		m_pstMaterialArray[ ii ].m_pcConstantBuffer = pnew CConstantBuffer( cConstantBufferData );

		m_pstMaterialArray[ ii ].m_pcTexture = pnew CDirectXTexture();
		pnew CDirectXTextureCreatorFromFile( m_pstMaterialArray[ ii ].m_pcTexture, pstMaterialArray[ii].m_sTexturePath, true );
	}
}
