/**
  * @file	ConstantBuffer.hlsli
  * @brief	コンスタントバッファー定義。
  * @date 2015/09/23 16:42:33
  */

cbuffer CBufForFrame	: register( b0 )
{
	float4x4	c_mtxDummyForFrame;	///< ダミー用。 
};

cbuffer CBufForLevel	: register( b1 )
{
	float4x4	c_mtxView;
	float4x4	c_mtxProjection;
};

cbuffer CBufForObject	: register( b2 )
{
	float4x4	c_mtxWorld;
};

cbuffer CBufForMaterial	: register( b3 )
{
	float4		c_vecDiffuse;
	float4		c_vecAmbient;
	float4		c_vecSpecular;
}

struct StVertexShaderOutput
{
	float4	m_fPos	: SV_POSITION;
	float2	m_fTex	: TEXCOORD;
};