/**
  * @file	ShaderDefintion.h
  * @brief	使用するシェーダーの定義。
  * @date 2015/09/13 04:20:35
  */

#ifndef INCLUDE_LIB_RENDER_SHADER_DEFINITION_H
#define INCLUDE_LIB_RENDER_SHADER_DEFINITION_H

/// 頂点シェーダー。
enum class EnVertexShader	: U32
{
	enSpriteShader,
	en3DShader,
	enMax,
};

/// ピクセルシェーダー。
enum class EnPixelShader : U32
{
	enSpriteShader,
	en3DShader,
	enMax,
};

#endif // #ifndef INCLUDE_LIB_RENDER_SHADER_DEFINITION_H
