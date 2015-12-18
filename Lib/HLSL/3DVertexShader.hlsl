/**
  * @file	3DVertexShader.hlsl
  * @brief	3D 描画頂点シェーダ。
  * @data 2015/12/05 12:46:35
  */

#include "3DShader.hlsli"

StVertexShaderOutput main( float4 _fPos : POSITION, float4 _fNormal : NORMAL, float2 _fTex : TEXCOORD )
{
	StVertexShaderOutput stOutput;
	_fPos = mul( _fPos, c_mtxWorld );
	_fPos = mul( _fPos, c_mtxView );
	stOutput.m_fPos = mul( _fPos, c_mtxProjection );
	stOutput.m_fTex = _fTex;
	return stOutput;
}
