/**
  * @file	Mesh.h
  * @brief	�|���S�����b�V���C���^�[�t�F�C�X�B
  * @data 2015/12/03 01:24:39
  */

#ifndef INCLUDE_LIB_MESH_H
#define INCLUDE_LIB_MESH_H

#include "Lib/Math/Vector.h"

/*
 * @class IMesh
 * @brief �|���S�����b�V���C���^�[�t�F�C�X�B
 */
class IMesh
{
public:
	/// ���_���B
	struct StVertex
	{
		StVector3D<F32>	m_stPos;		///< ���_���W�B
		StVector3D<F32>	m_stNormal;		///< �@���x�N�g���B
		StVector2D<F32>	m_stUV;			///< UV���W�B

		void Init()
		{
			m_stPos.Init();
			m_stNormal.Init();
			m_stUV.Init();
		}
	};

	/// �}�e���A�����B
	struct StMaterial
	{
		U32					m_uVertexNum;						///< ���_���B
		TChar				m_sTexturePath[ MAX_PATH + 1 ];		///< �e�N�X�`���t�@�C���ւ̃p�X�B
		StVector4D<F32>		m_stDiffuse;						///< �����ւ̔��ˋ��x�B
		StVector4D<F32>		m_stAmbient;						///< �g�U���ˌ��ւ̔��ˋ��x�B
		StVector4D<F32>		m_stSpecular;						///< ���ʔ��ˌ��ւ̔��ˋ��x�B

		void Init()
		{
			m_uVertexNum = 0;
			MemClear( m_sTexturePath, sizeof( m_sTexturePath ) );
			m_stDiffuse.Init();
			m_stAmbient.Init();
			m_stSpecular.Init();
		}
	};

public:
	/// �R���X�g���N�^�B
	IMesh(){}
	/// �f�X�g���N�^�B
	virtual ~IMesh(){}

	virtual U32					GetVertexNum() const = 0;		///< ���_��񐔂��擾�B
	virtual const StVertex*		GetVertexArray() const = 0;		///< ���_���z����擾�B
	virtual U32					GetIndexNum() const = 0;		///< �C���f�b�N�X�����擾�B
	virtual const U32*			GetIndexArray() const = 0;		///< �C���f�b�N�X�z����擾�B
	virtual U32					GetMaterialNum() const = 0;		///< �}�e���A�������擾�B
	virtual const StMaterial*	GetMaterialArray() const = 0;	///< �}�e���A���z����擾�B
};

#endif // #ifndef INCLUDE_LIB_MESH_H
