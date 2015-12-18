/**
  * @file	ShaderDefintion.h
  * @brief	�g�p����V�F�[�_�[�̒�`�B
  * @date 2015/09/13 04:20:35
  */

#ifndef INCLUDE_LIB_RENDER_SHADER_DEFINITION_H
#define INCLUDE_LIB_RENDER_SHADER_DEFINITION_H

/// ���_�V�F�[�_�[�B
enum class EnVertexShader	: U32
{
	enSpriteShader,
	en3DShader,
	enMax,
};

/// �s�N�Z���V�F�[�_�[�B
enum class EnPixelShader : U32
{
	enSpriteShader,
	en3DShader,
	enMax,
};

#endif // #ifndef INCLUDE_LIB_RENDER_SHADER_DEFINITION_H
