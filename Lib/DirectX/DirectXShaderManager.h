/**
  * @file	DirectXShaderManager.h
  * @brief	�V�F�[�_�[�Ǘ��N���X�B
  * @date 2015/09/13 04:16:50
  */

#ifndef INCLUDE_LIB_DIRECTX_SHADERMANAGER_H
#define INCLUDE_LIB_DIRECTX_SHADERMANAGER_H

#include "Lib/DirectX/DirectXShaderDefinition.h"

class CVertexShader;
class CPixelShader;

/*
 * @class CDirectXShaderManager
 * @brief �V�F�[�_�[�Ǘ��N���X�B
 */
class CDirectXShaderManager
{
public:
	/// �R���X�g���N�^�B
	CDirectXShaderManager();
	/// �f�X�g���N�^�B
	virtual ~CDirectXShaderManager();

	/// ���_�V�F�[�_�[���擾�B
	const CVertexShader* GetVertexShader( EnVertexShader _eVertexShader ) const;
	/// �s�N�Z���V�F�[�_�[���擾�B
	const CPixelShader* GetPixelShader( EnPixelShader _ePixelShader )const;

	/// �ǂݍ��݂������������B
	bool IsReadEnd() const;

private:
	CVertexShader*	m_pcVertexShaderArray[ s_cast<U32>(EnVertexShader::enMax) ];
	CPixelShader*	m_pcPixelShaderArray[ s_cast<U32>(EnPixelShader::enMax) ];
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_SHADERMANAGER_H