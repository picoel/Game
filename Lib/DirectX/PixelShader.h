/**
  * @file	PixelShader.h
  * @brief	DirectX11用ピクセルシェーダークラス。
  * @date 2015/07/06 01:42:38
  */

#ifndef INCLUDE_LIB_DIRECTX_PIXELSHADER_H
#define INCLUDE_LIB_DIRECTX_PIXELSHADER_H

#include "Lib/File/FileReader.h"

class CRenderContextDX11;

/*
 * @class CPixelShader
 * @brief DirectX11用ピクセルシェーダークラス。
 */
class CPixelShader : public CFileReader
{
public:
	/// 初期化用パラメータ。
	struct StInitParam
	{
		const TChar*			m_psFileName;

		void Init()
		{
			m_psFileName = nullptr;
		}
	};

public:
	/// コンストラクタ。
	CPixelShader( const StInitParam& _rstInitParam );
	/// デストラクタ。
	virtual ~CPixelShader();

	/// 読み込み完了時の処理。
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// シェーダーを取得。
	ID3DPixelShader* GetShader() const{ return m_pcPixelShader; }

private:
	ID3DPixelShader*		m_pcPixelShader;

};

#endif // #ifndef INCLUDE_LIB_DIRECTX_PIXELSHADER_H
