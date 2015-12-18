/**
  * @file	ConstantBufferDataForFrame.cpp
  * @brief	���x���p�̃R���X�^���g�o�b�t�@�[�B
  * @date 2015/09/23 17:06:06
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Render/ConstantBufferDataForFrame.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CConstantBufferDataForFrame::CConstantBufferDataForFrame()
	: IConstantBufferData()
	, m_stBuffer()
{
	m_stBuffer.Init();
}

