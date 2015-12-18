/**
  * @file	VertexShader.h
  * @brief	頂点シェーダークラス。
  * @date 2015/06/06 11:51:58
  */

#ifndef INCLUDE_DIRECTX11_VERTEXSHADER_H
#define INCLUDE_DIRECTX11_VERTEXSHADER_H

#include "Lib/File/FileReader.h"

class CRenderContextDX11;

/*
 * @class	CVertexShader.h
 * @brief	頂点シェーダークラス。
 */
class CVertexShader	: public CFileReader
{
public:
	/// 初期化用パラメータ。
	struct StInitParam
	{
		const TChar*				m_psFileName;

		void Init()
		{
			m_psFileName = nullptr;
		}
	};

public:
	/// コンストラクタ。
	CVertexShader( const StInitParam& _rstInitParam );
	/// デストラクタ。
	virtual ~CVertexShader();

	/// 読み込み完了時の処理。
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// シェーダーを取得。
	ID3DVertexShader* GetShader() const{ return m_pcVertexShader; }
	/// 入力レイアウトを取得。
	ID3DInputLayout* GetInputLayout() const{ return m_pcInputLayout; }

private:
	/// DXGIフォーマットを取得。
	DXGI_FORMAT GetDxgiFormat( D3D_REGISTER_COMPONENT_TYPE _uType, U32 _uMask );

private:
	ID3DVertexShader*			m_pcVertexShader;
	ID3DInputLayout*			m_pcInputLayout;
};

#endif // #ifndef INCLUDE_DIRECTX11_VERTEXSHADER_H
