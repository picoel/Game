/**
  * @file	SpritePixelShader.hlsl
  * @brief	�X�v���C�g �`��s�N�Z���V�F�[�_�[�B
  * @date 2015/06/06 12:10:37
  */
#include "SpriteShader.hlsli"

float4 main( StSpriteVertexShaderOutput _stInput ) : SV_TARGET
{
	return g_cTexDecal.Sample( g_cSamLinear, _stInput.m_fTex );
}
