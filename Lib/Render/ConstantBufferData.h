/**
  * @file	CostantBuffer.h
  * @brief	�R���X�^���g�o�b�t�@�[�B
  * @date 2015/09/23 16:58:22
  */

#ifndef INCLUDE_LIB_RENDER_CONSTANT_BUFFER_H
#define INCLUDE_LIB_RENDER_CONSTANT_BUFFER_H

/// �R���X�^���g�o�b�t�@�[�̎�ށB
enum class EnConstantBuffer : U32
{
	enFrame,		///< �t���[���p�B
	enLevel,		///< ���x���p�B
	enObject,		///< �I�u�W�F�N�g�p�B
	enMaterial,		///< �}�e���A���p�B
	enMax,
};

/*
 * @class IConstantBufferData
 * @brief �R���X�^���g�o�b�t�@�[�̃C���^�[�t�F�[�X�B
 */
class IConstantBufferData
{
public:
	/// �R���X�g���N�^�B
	IConstantBufferData(){}
	/// �f�X�g���N�^�B
	virtual ~IConstantBufferData(){}

	/// �R���X�^���g�o�b�t�@�[�ɃR�s�[����f�[�^���擾�B
	virtual const void* GetData() const = 0;
	/// �R���X�^���g�o�b�t�@�[�ɃR�s�[����f�[�^�̃T�C�Y���擾�B
	virtual USize GetSize() const = 0;
};

#endif // #ifndef INCLUDE_LIB_RENDER_CONSTANT_BUFFER_H
