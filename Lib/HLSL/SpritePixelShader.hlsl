/**
  * @file	SpritePixelShader.hlsl
  * @brief	スプライト 描画ピクセルシェーダー。
  * @date 2015/06/06 12:10:37
  */
#include "SpriteShader.hlsli"

float4 main( StSpriteVertexShaderOutput _stInput ) : SV_TARGET
{
	return g_cTexDecal.Sample( g_cSamLinear, _stInput.m_fTex );
}
