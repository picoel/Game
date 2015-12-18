/**
  * @file	DirectXTexture.h
  * @brief	DirectX�p�e�N�X�`���N���X�B
  * @date	2015/08/09 02:10:29
  */

#ifndef INCLUDE_DIRECTX_TEXTURE_H
#define INCLUDE_DIRECTX_TEXTURE_H

#include "Lib/File/FileReader.h"

/*
 * @class CDirectXTexture
 * @brief DirectX�p�e�N�X�`���N���X�B
 */
class CDirectXTexture
{
public:
	/// �R���X�g���N�^�B
	CDirectXTexture();
	/// �f�X�g���N�^�B
	virtual ~CDirectXTexture();

	/// �e�N�X�`�����쐬�B
	void CreateTexture( const D3D_TEXTURE2D_DESC& _rstDesc );
	void CreateTexture( const DirectX::ScratchImage& _rstImage, const DirectX::TexMetadata& _rstMetaData );

	/// �쐬�ς݂��B
	bool IsCreate() const{ return m_bIsCreate; }

	/// �e�N�X�`����ݒ�B
	

protected:
	ID3DTexture2D*			m_pcTexture;
	ID3DShaderResourceView*	m_pcResourceView;
	bool			m_bIsCreate;
};

/*
 * @class CDirectXTextureReader
 * @brief �t�@�C������摜��ǂݍ��ށB
 */
class CDirectXTextureReader
	: public CFileReader
{
public:
	/// �R���X�g���N�^�B
	CDirectXTextureReader( const TChar* _psFileName );
	CDirectXTextureReader( const TChar* _psFileName, nLib::nDirectX::EnTextureFormat _eFormat);
	/// �f�X�g���N�^�B
	virtual ~CDirectXTextureReader(){}

	/// �ǂݍ��݊������̏����B
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// �摜�f�[�^���擾�B
	const DirectX::ScratchImage& GetImage() const{ return m_stImage; }
	/// ���^�f�[�^���擾�B
	const DirectX::TexMetadata& GetMetadata() const{ return m_stMetaData; }

private:
	nLib::nDirectX::EnTextureFormat	m_eFormat;

	DirectX::ScratchImage	m_stImage;
	DirectX::TexMetadata	m_stMetaData;
};

/*
 * @class CDirectXTextureCreatorFromFile
 * @brief �t�@�C������摜��ǂݍ��݃e�N�X�`�����쐬����B
 */
class CDirectXTextureCreatorFromFile
	: public CDirectXTextureReader
{
public:
	/// �R���X�g���N�^�B
	CDirectXTextureCreatorFromFile( CDirectXTexture* _pcTexture, const TChar* _psFileName, bool _bIsSuicide );
	/// �f�X�g���N�^�B
	virtual ~CDirectXTextureCreatorFromFile(){}

	/// �ǂݍ��݊������̏����B
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;
	/// �ǂݍ��݊������̏���(���C���X���b�h�Ɠ���)�B
	virtual void ReadEndProcessSync() override;

private:
	CDirectXTexture*	m_pcTexture;
	bool				m_bIsSuicide;
};

#endif // #ifndef INCLUDE_DIRECTX_TEXTURE_H