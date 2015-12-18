/**
  * @file	RenderContext.h
  * @brief	�`��R���e�L�X�g�B
  * @date 2015/05/21 06:06:18
  */

#ifndef INCLUDE_RENDER_CONTEXT_H
#define INCLUDE_RENDER_CONTEXT_H

#include "Lib/Render/ConstantBufferData.h"

/*
 * @class IRenderContext
 * @brief �`��R���e�L�X�g�C���^�[�t�F�[�X�B
 */
class IRenderContext
{
public:
	/// �f�X�g���N�^�B
	virtual ~IRenderContext(){}

	/// �`��B
	virtual void Render() = 0;
	/// ��ʂ̃N���A�B
	virtual void Clear() = 0;

	/// �|���S����`��B
	virtual void DrawIndexed( U32 _uIndexNum, U32 _uOffset ) = 0;

	/// �g�p�\���ǂ����B
	virtual bool IsEnabled() const{ return true; }

	//#TODO �`��ɕK�v�ȏ�����ǉ�����B

	/// �R���X�^���g�o�b�t�@�̍X�V�B
	virtual void UpdateConstantBuffer( void* _pcBuffer, const IConstantBufferData& _rcData ) = 0;
	/// �R���X�^���g�o�b�t�@�̐ݒ�B
	virtual void SetConstantBuffer( EnConstantBuffer _eKind, void* _pcConstantBuffer ) = 0;

	/// ���_�o�b�t�@�̐ݒ�B
	virtual void SetVertexBuffer( U32 _uSlot, void* _pcBuffer, U32 _uStride, U32 _uOffset ) = 0;
	/// �C���f�b�N�X�o�b�t�@�̐ݒ�B
	virtual void SetIndexBuffer( void* _pcBuffer, U32 _uOffset ) = 0;
	/// �v���~�e�B�u�g�|���W�[��ݒ�B
	virtual void SetPrimitiveTopology( U32 _uPrimitive ) = 0;

	/// �e�N�X�`����ݒ�B
	virtual void SetTexture( U32 _uSlot, void* _pcTexture ) = 0;

	/// ���_�V�F�[�_�[�̐ݒ�B
	virtual void SetVertexShader( EnVertexShader _eShader ) = 0;
	/// �s�N�Z���V�F�[�_�[�̐ݒ�B
	virtual void SetPixelShader( EnPixelShader _eShader ) = 0;
};

#endif // #ifndef INCLUDE_RENDER_CONTEXT_H
