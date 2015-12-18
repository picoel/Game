/**
  * @file	SpriteVertexShader.hlsl
  * @brief	スプライト描画用シェーダー
  * @date 2015/05/30 19:42:26
  */

#include "SpriteShader.hlsli"

StSpriteVertexShaderOutput main( float4 _fPos : POSITION, float4 _fNormal : NORMAL, float2 _fTex : TEXCOORD )
{
	StSpriteVertexShaderOutput	stOutput;
	stOutput.m_fPos = _fPos;
	stOutput.m_fTex = _fTex;
	return stOutput;
}
