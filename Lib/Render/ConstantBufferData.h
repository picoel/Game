/**
  * @file	CostantBuffer.h
  * @brief	コンスタントバッファー。
  * @date 2015/09/23 16:58:22
  */

#ifndef INCLUDE_LIB_RENDER_CONSTANT_BUFFER_H
#define INCLUDE_LIB_RENDER_CONSTANT_BUFFER_H

/// コンスタントバッファーの種類。
enum class EnConstantBuffer : U32
{
	enFrame,		///< フレーム用。
	enLevel,		///< レベル用。
	enObject,		///< オブジェクト用。
	enMaterial,		///< マテリアル用。
	enMax,
};

/*
 * @class IConstantBufferData
 * @brief コンスタントバッファーのインターフェース。
 */
class IConstantBufferData
{
public:
	/// コンストラクタ。
	IConstantBufferData(){}
	/// デストラクタ。
	virtual ~IConstantBufferData(){}

	/// コンスタントバッファーにコピーするデータを取得。
	virtual const void* GetData() const = 0;
	/// コンスタントバッファーにコピーするデータのサイズを取得。
	virtual USize GetSize() const = 0;
};

#endif // #ifndef INCLUDE_LIB_RENDER_CONSTANT_BUFFER_H
