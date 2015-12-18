/**
  * @file	PMDMesh.h
  * @brief	PMD�`���̃|���S�����b�V���B
  * @data 2015/12/03 01:30:57
  */

#ifndef INCLUDE_LIB_PMD_PMDMESH_H
#define INCLUDE_LIB_PMD_PMDMESH_H

#include "Lib/Mesh/Mesh.h"

class CPMDReader;

/*
 * @class CPMDMesh
 * @brief PMD�`���̃|���S�����b�V���B
 */
class CPMDMesh : public IMesh
{
public:
	/// �R���X�g���N�^�B
	CPMDMesh( const CPMDReader& _rcReader );
	/// �f�X�g���N�^�B
	virtual ~CPMDMesh();

	/// ���_���W�����擾�B
	virtual U32 GetVertexNum() const override{ return m_uVertexNum; }
	/// ���_���W�z����擾�B
	virtual const StVertex* GetVertexArray() const override{ return m_pstVertexArray; }
	/// �C���f�b�N�X�����擾�B
	virtual U32 GetIndexNum() const override{ return m_uIndexNum; }
	/// �C���f�b�N�X�z����擾�B
	virtual const U32* GetIndexArray() const override{ return m_puIndexArray; }
	/// �}�e���A�������擾�B
	virtual U32 GetMaterialNum() const override{ return m_uMaterialNum; }
	/// �}�e���A���z����擾�B
	virtual const StMaterial* GetMaterialArray() const override{ return m_pstMaterialArray; }

private:
	/// ���_���𒊏o�B
	void ExtractVertex( const CPMDReader& _rcReader );
	/// �C���f�b�N���𒊏o�B
	void ExtractIndex( const CPMDReader& _rcReader );
	/// �}�e���A�����𒊏o�B
	void ExtractMaterial( const CPMDReader& _rcReader );

private:
	U32			m_uVertexNum;			///< ���_��񐔁B
	StVertex*	m_pstVertexArray;		///< ���_���z��B

	U32			m_uIndexNum;			///< �C���f�b�N�X���B
	U32*		m_puIndexArray;			///< �C���f�b�N�z��B

	U32			m_uMaterialNum;			///< �}�e���A�����B
	StMaterial*	m_pstMaterialArray;		///< �}�e���A�����z��B
};

#endif // #ifndef INCLUDE_LIB_PMD_PMDMESH_H