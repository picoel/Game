/**
  * @file	3DShader.hlsli
  * @brief	3D描画シェーダ。
  * @data 2015/12/05 12:47:54
  */

#include "ConstantBuffer.hlsli"

Texture2D			g_cTexDecal		: register( t0 );
SamplerState		g_cSamLinear	: register( s0 );
