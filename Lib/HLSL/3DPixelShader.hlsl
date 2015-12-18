/**
  * @file	3DPixelShader.hlsl
  * @brief	3D 描画ピクセルシェーダ。
  * @data 2015/12/05 12:46:35
  */

#include "3DShader.hlsli"

float4 main( StVertexShaderOutput _stInput) : SV_TARGET
{
	return g_cTexDecal.Sample( g_cSamLinear, _stInput.m_fTex );
}