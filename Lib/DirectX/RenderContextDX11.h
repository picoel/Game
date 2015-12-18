/**
  * @file	RenderContextDX11.h
  * @brief	DirectX11 �`��R���e�L�X�g�B
  * @date 2015/05/21 06:18:57
  */

#ifndef INCLUDE_RENDER_CONTEXT_DX11_H
#define INCLUDE_RENDER_CONTEXT_DX11_H

#if defined( USE_DIRECTX_11 )

#include "Lib/Render/RenderContext.h"
#include "Lib/Thread/CriticalSection.h"

class CVertexShader;
class CPixelShader;
class CDirectXTexture;
class CDirectXShaderManager;

/*
 * @class CRenderContextDX11
 * @brief DirectX11 �`��R���e�L�X�g�B
 */
class CRenderContextDX11 : public  IRenderContext
{
public:
	struct StInitParam
	{
		HWND	m_hWnd;
		U32		m_uWidth;
		U32		m_uHeight;

		void Init()
		{
			m_hWnd = NULL;
			m_uWidth = 0;
			m_uHeight = 0;
		}
	};

public:
	/// �R���X�g���N�^�B
	CRenderContextDX11( const StInitParam& _rstInitParam );
	/// �f�X�g���N�^�B
	virtual ~CRenderContextDX11();

	/// �`��B
	virtual void Render() final;
	/// ��ʂ̃N���A�B
	virtual void Clear() final;

	/// �|���S���̕`��B
	virtual void DrawIndexed( U32 _uIndexNum, U32 _uOffset ) override final;

	/// �g�p�\���ǂ����B
	virtual bool IsEnabled() const override final;

	/// �R���X�^���g�o�b�t�@�̍X�V�B
	virtual void UpdateConstantBuffer( void* _pcBuffer, const IConstantBufferData& _rcData );
	/// �R���X�^���g�o�b�t�@�[�̐ݒ�B
	virtual void SetConstantBuffer( EnConstantBuffer _eKind, void* _pcBuffer ) override final;
	
	/// ���_�o�b�t�@�̐ݒ�B
	virtual void SetVertexBuffer( U32 _uSlot, void* _pcBuffer, U32 _uStride, U32 _uOffset ) override final;
	/// �C���f�b�N�X�o�b�t�@�̐ݒ�B
	virtual void SetIndexBuffer( void* _pcBuffer, U32 _uOffset ) override final;
	/// �v���~�e�B�u�g�|���W�[��ݒ�B
	virtual void SetPrimitiveTopology( U32 _uPrimitive ) override final;

	/// �e�N�X�`����ݒ�B
	virtual void SetTexture( U32 _uSlot, void* _pcTexture ) override final;

	/// ���_�V�F�[�_�[�̐ݒ�B
	virtual void SetVertexShader( EnVertexShader _eShader ) override final;
	/// �s�N�Z���V�F�[�_�[�̐ݒ�B
	virtual void SetPixelShader( EnPixelShader _eShader ) override final;

private:
	/// �������B
	bool Init();

	/// DirectX�̏�����	: �X���b�v�`�F�C���̍쐬�B
	bool InitDirectX_CreateSwapChain();
	/// DirectX�̏����� : �����_�[�^�[�Q�b�g�̐����B
	bool InitDirectX_CreateRenderTargetView();
	/// DirectX�̏����� : Z�o�b�t�@�̍쐬�B
	bool InitDirectX_CreateZBuffer();
	/// DirectX�̏����� : �r���[�|�[�g�̐ݒ�B
	bool InitDirectX_SetupViewPort();

private:
	StInitParam		m_stInitParam;

	ID3D11Device*				m_pcDevice;				///< DirectX11�f�o�C�X�B
	ID3D11DeviceContext*		m_pcContext;			///< DirectX11�`��R���e�L�X�g�B
	IDXGISwapChain*				m_pcSwapChain;			///< �o�b�N�o�b�t�@�̐���B
	ID3D11Texture2D*			m_pcBackBuffer;			///< �o�b�N�o�b�t�@�B
	ID3D11RenderTargetView*		m_pcRenderTargetView;	///< �����_�[�^�[�Q�b�g�B
	ID3D11DepthStencilView*		m_pcDepthStencilView;	///< �[�x�X�e���V���r���[�B
	ID3D11Texture2D*			m_pcDepthStencilBuffer;	///< �[�x�X�e���V���o�b�t�@�B
	D3D_FEATURE_LEVEL			m_eFeatureLevel;		///< �@�\���x���B

	CCriticalSection			m_cCriticalSection;		///< �N���e�B�J���Z�N�V�����B

	CDirectXShaderManager*		m_pcShaderManager;		///< �V�F�[�_�[�Ǘ��B
};

#endif // #if defined( USE_DIRECTX_11 )

#endif // #ifndef INCLUDE_RENDER_CONTEXT_DX11_H