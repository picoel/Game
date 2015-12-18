/**
  * @file	ConstantBufferDataForMaterial.h
  * @brief	マテリアル用のコンスタントバッファ。
  * @data 2015/12/12 18:01:06
  */
#ifndef INCLUDE_LIB_RENDRE_CONSTANT_BUFFER_FOR_MATERIAL_H
#define INCLUDE_LIB_RENDRE_CONSTANT_BUFFER_FOR_MATERIAL_H

#include "Lib/Render/ConstantBufferData.h"
#include "Lib/Math/Vector.h"

/*
 * @class CConstantBufferDataForMaterial
 * @brief マテリアル用のコンスタントバッファ。
 */
class CConstantBufferDataForMaterial : public IConstantBufferData
{
public:
	/// コンスタントバッファ構造体。
	struct StConstantBufferData
	{
		StVector4D<F32>	m_stVecDiffuse;
		StVector4D<F32>	m_stVecAmbient;
		StVector4D<F32>	m_stVecSpecular;

		void Init()
		{
			m_stVecDiffuse.Init();
			m_stVecAmbient.Init();
			m_stVecSpecular.Init();
		}
	};

public:
	/// コンストラクタ。
	CConstantBufferDataForMaterial();
	/// デストラクタ。
	virtual ~CConstantBufferDataForMaterial(){}

	/// データを取得。
	virtual const void* GetData() const override{ return &m_stConstantBufferData; }
	/// データサイズを取得。
	virtual USize GetSize() const override{ return sizeof( StConstantBufferData ); }

	/// ディフューズを設定。
	void SetDiffuse( const StVector4D<F32>& _rstDiffuse );
	/// アンビエントを設定。
	void SetAmbient( const StVector4D<F32>& _rstAmbient );
	/// スペキュラーを設定。
	void SetSpecular( const StVector4D<F32>& _rstSpecular );

private:
	StConstantBufferData	m_stConstantBufferData;
};

#endif // #ifndef INCLUDE_LIB_RENDRE_CONSTANT_BUFFER_FOR_MATERIAL_H