/**
  * @file	MeshDrawer.h
  * @brief	メッシュ描画。
  * @data 2015/12/03 06:26:54
  */
#ifndef INCLUDE_LIB_MESH_MESHDRAWER_H
#define INCLUDE_LIB_MESH_MESHDRAWER_H

#include "Lib/Mesh/Mesh.h"

class CDirectXTexture;
class IRenderContext;
class CConstantBuffer;

/*
 * @class CMeshDrawer
 * @brief メッシュの描画。
 */
class CMeshDrawer
{
public:
	/// コンストラクタ。
	CMeshDrawer( const IMesh* _pcMesh );
	/// デストラクタ。
	virtual ~CMeshDrawer();

	/// 描画処理。
	void Draw( IRenderContext* _pcContext );
	/// 読み込みが完了したか。
	bool IsReadEnd() const;

private:
	/// 頂点バッファーの作成。
	void CreateVertexBuffer( const IMesh* _pcMesh );
	/// インデックスバッファーの作成。
	void CreateIndexBuffer( const IMesh* _pcMesh );
	/// マテリアル情報の作成。
	void CreateMaterial( const IMesh* _pcMesh );

private:
	struct StMaterial
	{
		U32								m_uVertexNum;
		CConstantBuffer*				m_pcConstantBuffer;
		CDirectXTexture*				m_pcTexture;
		
		void Init()
		{
			m_uVertexNum = 0;
			m_pcConstantBuffer = nullptr;
			m_pcTexture = nullptr;
		}
	};

private:
	ID3DBuffer*			m_pcVertexBuffer;
	ID3DBuffer*			m_pcIndexBuffer;

	U32					m_uMaterialNum;
	StMaterial*			m_pstMaterialArray;
};

#endif // #ifndef INCLUDE_LIB_MESH_MESHDRAWER_H