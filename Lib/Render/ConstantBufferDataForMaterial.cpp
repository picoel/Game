/**
  * @file	ConstantBufferForMaterial.cpp
  * @brief	�}�e���A���p�̃R���X�^���g�o�b�t�@�B
  * @data 2015/12/12 18:01:06
  */
#include "Lib/LibPrecompile.h"
#include "Lib/Render/ConstantBufferDataForMaterial.h"

/**
 * @brief		�R���X�g���N�^�B
 */
CConstantBufferDataForMaterial::CConstantBufferDataForMaterial()
	: IConstantBufferData()
	, m_stConstantBufferData()
{
	m_stConstantBufferData.Init();
}

/**
 * @brief		�f�B�t���[�Y��ݒ�B
 * @param[in]	_rstDiffuse	: �ݒ肷��f�B�t���[�Y�l�B
 */
void CConstantBufferDataForMaterial::SetDiffuse( const StVector4D<F32>& _rstDiffuse )
{
	MemCopy( &m_stConstantBufferData.m_stVecDiffuse, &_rstDiffuse, sizeof m_stConstantBufferData.m_stVecDiffuse );
}

/**
 * @brief		�A���r�G���g��ݒ�B
 * @param[in]	_rstDiffuse	: �ݒ肷��A���r�G���g�l�B
 */
void CConstantBufferDataForMaterial::SetAmbient( const StVector4D<F32>& _rstAmbient )
{
	MemCopy( &m_stConstantBufferData.m_stVecAmbient, &_rstAmbient, sizeof m_stConstantBufferData.m_stVecAmbient );
}

/**
 * @brief		�X�y�L�����[��ݒ�B
 * @param[in]	_rstDiffuse	: �ݒ肷��X�y�L�����[�l�B
 */
void CConstantBufferDataForMaterial::SetSpecular( const StVector4D<F32>& _rstSpecular )
{
	MemCopy( &m_stConstantBufferData.m_stVecSpecular, &_rstSpecular, sizeof m_stConstantBufferData.m_stVecSpecular );
}
