/**
  * @file	ConstantBufferDataForLevel.cpp
  * @brief	レベル用のコンスタントバッファー。
  * @date 2015/09/23 17:06:06
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Render/ConstantBufferDataForLevel.h"

/**
 * @brief	コンストラクタ。
 */
CConstantBufferDataForLevel::CConstantBufferDataForLevel()
	: IConstantBufferData()
	, m_stBuffer()
{
	m_stBuffer.Init();
}

