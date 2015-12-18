/**
  * @file	PMDMesh.cpp
  * @brief	PMD形式のポリゴンメッシュ。
  * @data 2015/12/03 01:30:57
  */
#include "Lib/LibPrecompile.h"
#include "Lib/PMD/PMDMesh.h"
#include "Lib/PMD/PMDReader.h"

#include "Lib/DirectX/DirectXTexture.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_rcReader	: PMD読み込みクラス。
 */
CPMDMesh::CPMDMesh( const CPMDReader& _rcReader )
	: m_uVertexNum( 0 )
	, m_pstVertexArray( nullptr )
	, m_uIndexNum( 0 )
	, m_puIndexArray( nullptr )
	, m_uMaterialNum( 0 )
	, m_pstMaterialArray( nullptr )
{
	ASSERT( _rcReader.IsReadEnd() );
	if (_rcReader.IsReadEnd())
	{
		ExtractVertex( _rcReader );
		ExtractIndex( _rcReader );
		ExtractMaterial( _rcReader );
	}
}

/**
 * @brief	デストラクタ。
 */
CPMDMesh::~CPMDMesh()
{
	P_DELETE_ARRAY( m_pstVertexArray );
	P_DELETE_ARRAY( m_puIndexArray );
	P_DELETE_ARRAY( m_pstMaterialArray );
}

/**
 * @brief		頂点情報を抽出。
 * @param[in]	_rcReader	: PMD読み込みクラス。
 */
void CPMDMesh::ExtractVertex( const CPMDReader& _rcReader )
{
	const meshio::pmd::IO& rstData = _rcReader.GetPMDData();
	m_uVertexNum = rstData.vertices.size();
	if (m_uVertexNum <= 0)
	{
		return;
	}

	ASSERT( nullptr == m_pstVertexArray );
	P_DELETE_ARRAY( m_pstVertexArray );
	m_pstVertexArray = pnew StVertex[ m_uVertexNum ];

	for (U32 ii = 0; ii < m_uVertexNum; ++ii)
	{
		m_pstVertexArray[ ii ].Init();

		m_pstVertexArray[ ii ].m_stPos.x = rstData.vertices[ ii ].pos.x;
		m_pstVertexArray[ ii ].m_stPos.y = rstData.vertices[ ii ].pos.y;
		m_pstVertexArray[ ii ].m_stPos.z = rstData.vertices[ ii ].pos.z;

		m_pstVertexArray[ ii ].m_stNormal.x = rstData.vertices[ ii ].normal.x;
		m_pstVertexArray[ ii ].m_stNormal.y = rstData.vertices[ ii ].normal.y;
		m_pstVertexArray[ ii ].m_stNormal.z = rstData.vertices[ ii ].normal.z;

		m_pstVertexArray[ ii ].m_stUV.x = rstData.vertices[ ii ].uv.x;
		m_pstVertexArray[ ii ].m_stUV.y = rstData.vertices[ ii ].uv.y;
	}
}

/**
 * @brief		インデックス情報を抽出。
 * @param[in]	_rcReader	: PMD読み込みクラス。
 */
void CPMDMesh::ExtractIndex( const CPMDReader& _rcReader )
{
	const meshio::pmd::IO& rstData = _rcReader.GetPMDData();
	m_uIndexNum = rstData.indices.size();
	if (m_uIndexNum <= 0)
	{
		return;
	}

	ASSERT( nullptr == m_puIndexArray );
	P_DELETE_ARRAY( m_puIndexArray );
	m_puIndexArray = pnew U32[ m_uIndexNum ];

	for (U32 ii = 0; ii < m_uIndexNum; ++ii)
	{
		m_puIndexArray[ ii ] = rstData.indices[ ii ];
	}
}

/**
 * @brief		マテリアル情報を抽出。
 * @param[in]	_rcReader	: PMD読み込みクラス。
 */
void CPMDMesh::ExtractMaterial( const CPMDReader& _rcReader )
{
	const meshio::pmd::IO& rstData = _rcReader.GetPMDData();
	m_uMaterialNum = rstData.materials.size();
	if (m_uMaterialNum <= 0)
	{
		return;
	}

	ASSERT( nullptr == m_pstMaterialArray );
	P_DELETE_ARRAY( m_pstMaterialArray );
	m_pstMaterialArray = pnew StMaterial[ m_uMaterialNum ];
	
	for (U32 ii = 0; ii < m_uMaterialNum; ++ii)
	{
		m_pstMaterialArray[ ii ].Init();

		m_pstMaterialArray[ ii ].m_uVertexNum = rstData.materials[ ii ].vertex_count;

		m_pstMaterialArray[ ii ].m_stDiffuse.r = rstData.materials[ ii ].diffuse.r;
		m_pstMaterialArray[ ii ].m_stDiffuse.g = rstData.materials[ ii ].diffuse.g;
		m_pstMaterialArray[ ii ].m_stDiffuse.b = rstData.materials[ ii ].diffuse.b;
		m_pstMaterialArray[ ii ].m_stDiffuse.a = rstData.materials[ ii ].diffuse.a;

		m_pstMaterialArray[ ii ].m_stAmbient.r = rstData.materials[ ii ].ambient.r;
		m_pstMaterialArray[ ii ].m_stAmbient.g = rstData.materials[ ii ].ambient.g;
		m_pstMaterialArray[ ii ].m_stAmbient.b = rstData.materials[ ii ].ambient.b;
		m_pstMaterialArray[ ii ].m_stAmbient.a = 1.0f;

		m_pstMaterialArray[ ii ].m_stSpecular.r = rstData.materials[ ii ].specular.r;
		m_pstMaterialArray[ ii ].m_stSpecular.g = rstData.materials[ ii ].specular.g;
		m_pstMaterialArray[ ii ].m_stSpecular.b = rstData.materials[ ii ].specular.b;
		m_pstMaterialArray[ ii ].m_stSpecular.a = 1.0f;

		// PMDファイルのパスからテクスチャファイルのパスを計算する。
		TChar sFullPath[ MAX_PATH + 1 ];	// NULL文字分+1。
		_fullpath( sFullPath, _rcReader.GetFileName(), lengthof( sFullPath ) );
		TChar sDrive[ MAX_PATH + 1 ];
		TChar sDir[ MAX_PATH + 1 ];
		TChar sExt[ MAX_PATH + 1 ];
		_splitpath( sFullPath, sDrive, sDir, nullptr, sExt );
		_stprintf( m_pstMaterialArray[ii].m_sTexturePath, "%s%s%s", sDrive, sDir, rstData.materials[ ii ].texture.str().c_str() );
	}
}