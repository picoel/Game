/**
  * @file	Mesh.h
  * @brief	ポリゴンメッシュインターフェイス。
  * @data 2015/12/03 01:24:39
  */

#ifndef INCLUDE_LIB_MESH_H
#define INCLUDE_LIB_MESH_H

#include "Lib/Math/Vector.h"

/*
 * @class IMesh
 * @brief ポリゴンメッシュインターフェイス。
 */
class IMesh
{
public:
	/// 頂点情報。
	struct StVertex
	{
		StVector3D<F32>	m_stPos;		///< 頂点座標。
		StVector3D<F32>	m_stNormal;		///< 法線ベクトル。
		StVector2D<F32>	m_stUV;			///< UV座標。

		void Init()
		{
			m_stPos.Init();
			m_stNormal.Init();
			m_stUV.Init();
		}
	};

	/// マテリアル情報。
	struct StMaterial
	{
		U32					m_uVertexNum;						///< 頂点数。
		TChar				m_sTexturePath[ MAX_PATH + 1 ];		///< テクスチャファイルへのパス。
		StVector4D<F32>		m_stDiffuse;						///< 環境光への反射強度。
		StVector4D<F32>		m_stAmbient;						///< 拡散反射光への反射強度。
		StVector4D<F32>		m_stSpecular;						///< 鏡面反射光への反射強度。

		void Init()
		{
			m_uVertexNum = 0;
			MemClear( m_sTexturePath, sizeof( m_sTexturePath ) );
			m_stDiffuse.Init();
			m_stAmbient.Init();
			m_stSpecular.Init();
		}
	};

public:
	/// コンストラクタ。
	IMesh(){}
	/// デストラクタ。
	virtual ~IMesh(){}

	virtual U32					GetVertexNum() const = 0;		///< 頂点情報数を取得。
	virtual const StVertex*		GetVertexArray() const = 0;		///< 頂点情報配列を取得。
	virtual U32					GetIndexNum() const = 0;		///< インデックス数を取得。
	virtual const U32*			GetIndexArray() const = 0;		///< インデックス配列を取得。
	virtual U32					GetMaterialNum() const = 0;		///< マテリアル数を取得。
	virtual const StMaterial*	GetMaterialArray() const = 0;	///< マテリアル配列を取得。
};

#endif // #ifndef INCLUDE_LIB_MESH_H
