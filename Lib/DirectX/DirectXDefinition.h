/**
  * @file	DirectXDefinition.h
  * @brief	Direct—p’è‹`B
  * @date 2015/05/04 03:01:48
  */

#ifndef INCLUDE_DIRECTXDEFINITION_H
#define INCLUDE_DIRECTXDEFINITION_H

#include "Lib/DirectX/DirectXShaderDefinition.h"
#include "Lib/DirectX/DirectXConstantBufferDefinition.h"

#define SAFE_RELEASE(p) if(p){ (p)->Release(); (p) = nullptr; }

// 
#if defined( USE_DIRECTX_11 )
using ID3DDevice				= ID3D11Device;
using ID3DDeviceContext			= ID3D11DeviceContext;
using ID3DVertexShader			= ID3D11VertexShader;
using ID3DPixelShader			= ID3D11PixelShader;
using ID3DShaderReflection		= ID3D11ShaderReflection;
using ID3DInputLayout			= ID3D11InputLayout;
using ID3DResource				= ID3D11Resource;
using ID3DTexture2D				= ID3D11Texture2D;
using ID3DShaderResourceView	= ID3D11ShaderResourceView;
using ID3DBuffer				= ID3D11Buffer;

using D3D_SHADER_DESC				= D3D11_SHADER_DESC;
using D3D_INPUT_ELEMENT_DESC		= D3D11_INPUT_ELEMENT_DESC;
using D3D_SIGNATURE_PARAMETER_DESC	= D3D11_SIGNATURE_PARAMETER_DESC;
using D3D_TEXTURE2D_DESC			= D3D11_TEXTURE2D_DESC;
using D3D_BUFFER_DESC				= D3D11_BUFFER_DESC;
using D3D_SUBRESOURCE_DATA			= D3D11_SUBRESOURCE_DATA;
using D3D_MAPPED_SUBRESOURCE		= D3D11_MAPPED_SUBRESOURCE;
using D3D_SHADER_RESOURCE_VIEW_DESC	= D3D11_SHADER_RESOURCE_VIEW_DESC;

#define IID_ID3DShaderReflection IID_ID3D11ShaderReflection

#define D3D_USAGE_DEFAULT			D3D11_USAGE_DEFAULT
#define D3D_USAGE_DYNAMIC			D3D11_USAGE_DYNAMIC
#define D3D_BIND_VERTEX_BUFFER		D3D11_BIND_VERTEX_BUFFER
#define D3D_BIND_INDEX_BUFFER		D3D11_BIND_INDEX_BUFFER
#define D3D_BIND_CONSTANT_BUFFER	D3D11_BIND_CONSTANT_BUFFER
#define D3D_CPU_ACCESS_WRITE		D3D11_CPU_ACCESS_WRITE

#endif //  #if defined( USE_DIRECTX_11 )

namespace nLib
{
	namespace nDirectX
	{
		enum class EnTextureFormat : U32
		{
			enDDS,
			enTGA,
			enWIC,

			enUnknown,
		};
	};
};

#endif // #ifndef INCLUDE_DIRECTXDEFINITION_H