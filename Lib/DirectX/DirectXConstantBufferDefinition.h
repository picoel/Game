/**
  * @file	DirectXConstantBufferDefinition.h
  * @brief	DirectX�p�R���X�^���g�o�b�t�@�[��`�B
  * @date 2015/09/24 00:44:19
  */

#ifndef INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_DEFINITION_H
#define INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_DEFINITION_H

#include "Lib/Render/ConstantBufferData.h"
#include "Lib/Render/ConstantBufferDataForFrame.h"
#include "Lib/Render/ConstantBufferDataForLevel.h"
#include "Lib/Render/ConstantBufferDataForObject.h"

namespace nDirectXData
{
	/*
	 * @struct	StConstantBufferInfo
	 * @brief	�R���X�^���g�o�b�t�@�[���B
	 */
	struct StConstantBufferInfo
	{
		USize	m_uSize;		///< �o�b�t�@�[�T�C�Y�B
	};

	const StConstantBufferInfo sc_stConstantBufferInfoArray[ s_cast<U32>(EnConstantBuffer::enMax)] =
	{
		{ sizeof( CConstantBufferDataForFrame::StConstantBufferData ), },
		{ sizeof( CConstantBufferDataForLevel ::StConstantBufferData ), },
		{ sizeof( CConstantBufferDataForObject::StConstantBufferData ), },
	};
}

#endif // #ifndef INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_DEFINITION_H