/**
  * @file	SpriteShader.hlsli
  * @brief	スプライト描画シェーダー。
  * @date 2015/06/06 12:08:37
  */

#include "ConstantBuffer.hlsli"

Texture2D		g_cTexDecal	:	register(t0);
SamplerState	g_cSamLinear:	register(s0);

struct StSpriteVertexShaderOutput
{
	float4 m_fPos : SV_POSITION;
	float2 m_fTex : TEXCOORD;
};
