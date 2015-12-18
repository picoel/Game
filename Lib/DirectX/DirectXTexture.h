/**
  * @file	DirectXTexture.h
  * @brief	DirectX用テクスチャクラス。
  * @date	2015/08/09 02:10:29
  */

#ifndef INCLUDE_DIRECTX_TEXTURE_H
#define INCLUDE_DIRECTX_TEXTURE_H

#include "Lib/File/FileReader.h"

/*
 * @class CDirectXTexture
 * @brief DirectX用テクスチャクラス。
 */
class CDirectXTexture
{
public:
	/// コンストラクタ。
	CDirectXTexture();
	/// デストラクタ。
	virtual ~CDirectXTexture();

	/// テクスチャを作成。
	void CreateTexture( const D3D_TEXTURE2D_DESC& _rstDesc );
	void CreateTexture( const DirectX::ScratchImage& _rstImage, const DirectX::TexMetadata& _rstMetaData );

	/// 作成済みか。
	bool IsCreate() const{ return m_bIsCreate; }

	/// テクスチャを設定。
	

protected:
	ID3DTexture2D*			m_pcTexture;
	ID3DShaderResourceView*	m_pcResourceView;
	bool			m_bIsCreate;
};

/*
 * @class CDirectXTextureReader
 * @brief ファイルから画像を読み込む。
 */
class CDirectXTextureReader
	: public CFileReader
{
public:
	/// コンストラクタ。
	CDirectXTextureReader( const TChar* _psFileName );
	CDirectXTextureReader( const TChar* _psFileName, nLib::nDirectX::EnTextureFormat _eFormat);
	/// デストラクタ。
	virtual ~CDirectXTextureReader(){}

	/// 読み込み完了時の処理。
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// 画像データを取得。
	const DirectX::ScratchImage& GetImage() const{ return m_stImage; }
	/// メタデータを取得。
	const DirectX::TexMetadata& GetMetadata() const{ return m_stMetaData; }

private:
	nLib::nDirectX::EnTextureFormat	m_eFormat;

	DirectX::ScratchImage	m_stImage;
	DirectX::TexMetadata	m_stMetaData;
};

/*
 * @class CDirectXTextureCreatorFromFile
 * @brief ファイルから画像を読み込みテクスチャを作成する。
 */
class CDirectXTextureCreatorFromFile
	: public CDirectXTextureReader
{
public:
	/// コンストラクタ。
	CDirectXTextureCreatorFromFile( CDirectXTexture* _pcTexture, const TChar* _psFileName, bool _bIsSuicide );
	/// デストラクタ。
	virtual ~CDirectXTextureCreatorFromFile(){}

	/// 読み込み完了時の処理。
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;
	/// 読み込み完了時の処理(メインスレッドと同期)。
	virtual void ReadEndProcessSync() override;

private:
	CDirectXTexture*	m_pcTexture;
	bool				m_bIsSuicide;
};

#endif // #ifndef INCLUDE_DIRECTX_TEXTURE_H