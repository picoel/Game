/**
  * @file	DirectXShaderDefinition.h
  * @brief	DirectX用シェーダーの定義。
  * @date 2015/09/13 04:26:22
  */

#ifndef INCLUDE_LIB_DIRECTX_SHADER_DEFINITION_H
#define INCLUDE_LIB_DIRECTX_SHADER_DEFINITION_H

#include "Lib/Render/ShaderDefinition.h"

namespace nDirectXData
{
	/*
	 * @struct	StShaderInfo
	 * @brief	DirectX用シェーダー情報。
	 */
	struct StShaderInfo
	{
		TChar*	m_psFileName;	///< シェーダーファイル名。
	};

	/// 頂点シェーダー。
	const StShaderInfo	sc_stVertexShaderInfoArray[ s_cast<U32>(EnVertexShader::enMax) ] =
	{
		{ "SpriteVertexShader.cso" },
		{ "3DVertexShader.cso" }
	};

	/// ピクセルシェーダー。
	const StShaderInfo sc_stPixelShaderInfoArray[ s_cast<U32>(EnPixelShader::enMax) ] =
	{
		{ "SpritePixelShader.cso" },
		{ "3DPixelShader.cso" }
	};
}

#endif // #ifndef INCLUDE_LIB_DIRECTX_SHADER_DEFINITION_H