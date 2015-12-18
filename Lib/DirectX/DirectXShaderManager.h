/**
  * @file	DirectXShaderManager.h
  * @brief	シェーダー管理クラス。
  * @date 2015/09/13 04:16:50
  */

#ifndef INCLUDE_LIB_DIRECTX_SHADERMANAGER_H
#define INCLUDE_LIB_DIRECTX_SHADERMANAGER_H

#include "Lib/DirectX/DirectXShaderDefinition.h"

class CVertexShader;
class CPixelShader;

/*
 * @class CDirectXShaderManager
 * @brief シェーダー管理クラス。
 */
class CDirectXShaderManager
{
public:
	/// コンストラクタ。
	CDirectXShaderManager();
	/// デストラクタ。
	virtual ~CDirectXShaderManager();

	/// 頂点シェーダーを取得。
	const CVertexShader* GetVertexShader( EnVertexShader _eVertexShader ) const;
	/// ピクセルシェーダーを取得。
	const CPixelShader* GetPixelShader( EnPixelShader _ePixelShader )const;

	/// 読み込みが完了したか。
	bool IsReadEnd() const;

private:
	CVertexShader*	m_pcVertexShaderArray[ s_cast<U32>(EnVertexShader::enMax) ];
	CPixelShader*	m_pcPixelShaderArray[ s_cast<U32>(EnPixelShader::enMax) ];
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_SHADERMANAGER_H