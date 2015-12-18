/**
  * @file	PMDMesh.h
  * @brief	PMD形式のポリゴンメッシュ。
  * @data 2015/12/03 01:30:57
  */

#ifndef INCLUDE_LIB_PMD_PMDMESH_H
#define INCLUDE_LIB_PMD_PMDMESH_H

#include "Lib/Mesh/Mesh.h"

class CPMDReader;

/*
 * @class CPMDMesh
 * @brief PMD形式のポリゴンメッシュ。
 */
class CPMDMesh : public IMesh
{
public:
	/// コンストラクタ。
	CPMDMesh( const CPMDReader& _rcReader );
	/// デストラクタ。
	virtual ~CPMDMesh();

	/// 頂点座標数を取得。
	virtual U32 GetVertexNum() const override{ return m_uVertexNum; }
	/// 頂点座標配列を取得。
	virtual const StVertex* GetVertexArray() const override{ return m_pstVertexArray; }
	/// インデックス数を取得。
	virtual U32 GetIndexNum() const override{ return m_uIndexNum; }
	/// インデックス配列を取得。
	virtual const U32* GetIndexArray() const override{ return m_puIndexArray; }
	/// マテリアル数を取得。
	virtual U32 GetMaterialNum() const override{ return m_uMaterialNum; }
	/// マテリアル配列を取得。
	virtual const StMaterial* GetMaterialArray() const override{ return m_pstMaterialArray; }

private:
	/// 頂点情報を抽出。
	void ExtractVertex( const CPMDReader& _rcReader );
	/// インデック情報を抽出。
	void ExtractIndex( const CPMDReader& _rcReader );
	/// マテリアル情報を抽出。
	void ExtractMaterial( const CPMDReader& _rcReader );

private:
	U32			m_uVertexNum;			///< 頂点情報数。
	StVertex*	m_pstVertexArray;		///< 頂点情報配列。

	U32			m_uIndexNum;			///< インデックス数。
	U32*		m_puIndexArray;			///< インデック配列。

	U32			m_uMaterialNum;			///< マテリアル数。
	StMaterial*	m_pstMaterialArray;		///< マテリアル情報配列。
};

#endif // #ifndef INCLUDE_LIB_PMD_PMDMESH_H