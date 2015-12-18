/**
  * @file	ConstantBufferDataForMaterial.h
  * @brief	�}�e���A���p�̃R���X�^���g�o�b�t�@�B
  * @data 2015/12/12 18:01:06
  */
#ifndef INCLUDE_LIB_RENDRE_CONSTANT_BUFFER_FOR_MATERIAL_H
#define INCLUDE_LIB_RENDRE_CONSTANT_BUFFER_FOR_MATERIAL_H

#include "Lib/Render/ConstantBufferData.h"
#include "Lib/Math/Vector.h"

/*
 * @class CConstantBufferDataForMaterial
 * @brief �}�e���A���p�̃R���X�^���g�o�b�t�@�B
 */
class CConstantBufferDataForMaterial : public IConstantBufferData
{
public:
	/// �R���X�^���g�o�b�t�@�\���́B
	struct StConstantBufferData
	{
		StVector4D<F32>	m_stVecDiffuse;
		StVector4D<F32>	m_stVecAmbient;
		StVector4D<F32>	m_stVecSpecular;

		void Init()
		{
			m_stVecDiffuse.Init();
			m_stVecAmbient.Init();
			m_stVecSpecular.Init();
		}
	};

public:
	/// �R���X�g���N�^�B
	CConstantBufferDataForMaterial();
	/// �f�X�g���N�^�B
	virtual ~CConstantBufferDataForMaterial(){}

	/// �f�[�^���擾�B
	virtual const void* GetData() const override{ return &m_stConstantBufferData; }
	/// �f�[�^�T�C�Y���擾�B
	virtual USize GetSize() const override{ return sizeof( StConstantBufferData ); }

	/// �f�B�t���[�Y��ݒ�B
	void SetDiffuse( const StVector4D<F32>& _rstDiffuse );
	/// �A���r�G���g��ݒ�B
	void SetAmbient( const StVector4D<F32>& _rstAmbient );
	/// �X�y�L�����[��ݒ�B
	void SetSpecular( const StVector4D<F32>& _rstSpecular );

private:
	StConstantBufferData	m_stConstantBufferData;
};

#endif // #ifndef INCLUDE_LIB_RENDRE_CONSTANT_BUFFER_FOR_MATERIAL_H