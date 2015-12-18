/**
  * @file	ConstantBufferDataForObject.cpp
  * @brief	�I�u�W�F�N�g�p�̃R���X�^���g�o�b�t�@�[�B
  * @date 2015/09/23 17:06:06
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Render/ConstantBufferDataForObject.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CConstantBufferDataForObject::CConstantBufferDataForObject()
	: IConstantBufferData()
	, m_stBuffer()
{
	m_stBuffer.Init();
}

