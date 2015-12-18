/**
  * @file	VertexShader.h
  * @brief	���_�V�F�[�_�[�N���X�B
  * @date 2015/06/06 11:51:58
  */

#ifndef INCLUDE_DIRECTX11_VERTEXSHADER_H
#define INCLUDE_DIRECTX11_VERTEXSHADER_H

#include "Lib/File/FileReader.h"

class CRenderContextDX11;

/*
 * @class	CVertexShader.h
 * @brief	���_�V�F�[�_�[�N���X�B
 */
class CVertexShader	: public CFileReader
{
public:
	/// �������p�p�����[�^�B
	struct StInitParam
	{
		const TChar*				m_psFileName;

		void Init()
		{
			m_psFileName = nullptr;
		}
	};

public:
	/// �R���X�g���N�^�B
	CVertexShader( const StInitParam& _rstInitParam );
	/// �f�X�g���N�^�B
	virtual ~CVertexShader();

	/// �ǂݍ��݊������̏����B
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// �V�F�[�_�[���擾�B
	ID3DVertexShader* GetShader() const{ return m_pcVertexShader; }
	/// ���̓��C�A�E�g���擾�B
	ID3DInputLayout* GetInputLayout() const{ return m_pcInputLayout; }

private:
	/// DXGI�t�H�[�}�b�g���擾�B
	DXGI_FORMAT GetDxgiFormat( D3D_REGISTER_COMPONENT_TYPE _uType, U32 _uMask );

private:
	ID3DVertexShader*			m_pcVertexShader;
	ID3DInputLayout*			m_pcInputLayout;
};

#endif // #ifndef INCLUDE_DIRECTX11_VERTEXSHADER_H
