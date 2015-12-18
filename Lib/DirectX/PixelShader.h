/**
  * @file	PixelShader.h
  * @brief	DirectX11�p�s�N�Z���V�F�[�_�[�N���X�B
  * @date 2015/07/06 01:42:38
  */

#ifndef INCLUDE_LIB_DIRECTX_PIXELSHADER_H
#define INCLUDE_LIB_DIRECTX_PIXELSHADER_H

#include "Lib/File/FileReader.h"

class CRenderContextDX11;

/*
 * @class CPixelShader
 * @brief DirectX11�p�s�N�Z���V�F�[�_�[�N���X�B
 */
class CPixelShader : public CFileReader
{
public:
	/// �������p�p�����[�^�B
	struct StInitParam
	{
		const TChar*			m_psFileName;

		void Init()
		{
			m_psFileName = nullptr;
		}
	};

public:
	/// �R���X�g���N�^�B
	CPixelShader( const StInitParam& _rstInitParam );
	/// �f�X�g���N�^�B
	virtual ~CPixelShader();

	/// �ǂݍ��݊������̏����B
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// �V�F�[�_�[���擾�B
	ID3DPixelShader* GetShader() const{ return m_pcPixelShader; }

private:
	ID3DPixelShader*		m_pcPixelShader;

};

#endif // #ifndef INCLUDE_LIB_DIRECTX_PIXELSHADER_H
