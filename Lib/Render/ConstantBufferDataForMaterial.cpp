/**
  * @file	ConstantBufferForMaterial.cpp
  * @brief	マテリアル用のコンスタントバッファ。
  * @data 2015/12/12 18:01:06
  */
#include "Lib/LibPrecompile.h"
#include "Lib/Render/ConstantBufferDataForMaterial.h"

/**
 * @brief		コンストラクタ。
 */
CConstantBufferDataForMaterial::CConstantBufferDataForMaterial()
	: IConstantBufferData()
	, m_stConstantBufferData()
{
	m_stConstantBufferData.Init();
}

/**
 * @brief		ディフューズを設定。
 * @param[in]	_rstDiffuse	: 設定するディフューズ値。
 */
void CConstantBufferDataForMaterial::SetDiffuse( const StVector4D<F32>& _rstDiffuse )
{
	MemCopy( &m_stConstantBufferData.m_stVecDiffuse, &_rstDiffuse, sizeof m_stConstantBufferData.m_stVecDiffuse );
}

/**
 * @brief		アンビエントを設定。
 * @param[in]	_rstDiffuse	: 設定するアンビエント値。
 */
void CConstantBufferDataForMaterial::SetAmbient( const StVector4D<F32>& _rstAmbient )
{
	MemCopy( &m_stConstantBufferData.m_stVecAmbient, &_rstAmbient, sizeof m_stConstantBufferData.m_stVecAmbient );
}

/**
 * @brief		スペキュラーを設定。
 * @param[in]	_rstDiffuse	: 設定するスペキュラー値。
 */
void CConstantBufferDataForMaterial::SetSpecular( const StVector4D<F32>& _rstSpecular )
{
	MemCopy( &m_stConstantBufferData.m_stVecSpecular, &_rstSpecular, sizeof m_stConstantBufferData.m_stVecSpecular );
}
