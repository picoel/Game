/**
  * @file	ConstantBufferDataForFrame.cpp
  * @brief	レベル用のコンスタントバッファー。
  * @date 2015/09/23 17:06:06
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Render/ConstantBufferDataForFrame.h"

/**
 * @brief	コンストラクタ。
 */
CConstantBufferDataForFrame::CConstantBufferDataForFrame()
	: IConstantBufferData()
	, m_stBuffer()
{
	m_stBuffer.Init();
}

