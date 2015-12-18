/**
  * @file	DirectXShaderDefinition.h
  * @brief	DirectX�p�V�F�[�_�[�̒�`�B
  * @date 2015/09/13 04:26:22
  */

#ifndef INCLUDE_LIB_DIRECTX_SHADER_DEFINITION_H
#define INCLUDE_LIB_DIRECTX_SHADER_DEFINITION_H

#include "Lib/Render/ShaderDefinition.h"

namespace nDirectXData
{
	/*
	 * @struct	StShaderInfo
	 * @brief	DirectX�p�V�F�[�_�[���B
	 */
	struct StShaderInfo
	{
		TChar*	m_psFileName;	///< �V�F�[�_�[�t�@�C�����B
	};

	/// ���_�V�F�[�_�[�B
	const StShaderInfo	sc_stVertexShaderInfoArray[ s_cast<U32>(EnVertexShader::enMax) ] =
	{
		{ "SpriteVertexShader.cso" },
		{ "3DVertexShader.cso" }
	};

	/// �s�N�Z���V�F�[�_�[�B
	const StShaderInfo sc_stPixelShaderInfoArray[ s_cast<U32>(EnPixelShader::enMax) ] =
	{
		{ "SpritePixelShader.cso" },
		{ "3DPixelShader.cso" }
	};
}

#endif // #ifndef INCLUDE_LIB_DIRECTX_SHADER_DEFINITION_H