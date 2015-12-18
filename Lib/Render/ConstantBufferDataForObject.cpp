/**
  * @file	ConstantBufferDataForObject.cpp
  * @brief	オブジェクト用のコンスタントバッファー。
  * @date 2015/09/23 17:06:06
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Render/ConstantBufferDataForObject.h"

/**
 * @brief	コンストラクタ。
 */
CConstantBufferDataForObject::CConstantBufferDataForObject()
	: IConstantBufferData()
	, m_stBuffer()
{
	m_stBuffer.Init();
}

