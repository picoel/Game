/**
  * @file	MeshDrawer.h
  * @brief	���b�V���`��B
  * @data 2015/12/03 06:26:54
  */
#ifndef INCLUDE_LIB_MESH_MESHDRAWER_H
#define INCLUDE_LIB_MESH_MESHDRAWER_H

#include "Lib/Mesh/Mesh.h"

class CDirectXTexture;
class IRenderContext;
class CConstantBuffer;

/*
 * @class CMeshDrawer
 * @brief ���b�V���̕`��B
 */
class CMeshDrawer
{
public:
	/// �R���X�g���N�^�B
	CMeshDrawer( const IMesh* _pcMesh );
	/// �f�X�g���N�^�B
	virtual ~CMeshDrawer();

	/// �`�揈���B
	void Draw( IRenderContext* _pcContext );
	/// �ǂݍ��݂������������B
	bool IsReadEnd() const;

private:
	/// ���_�o�b�t�@�[�̍쐬�B
	void CreateVertexBuffer( const IMesh* _pcMesh );
	/// �C���f�b�N�X�o�b�t�@�[�̍쐬�B
	void CreateIndexBuffer( const IMesh* _pcMesh );
	/// �}�e���A�����̍쐬�B
	void CreateMaterial( const IMesh* _pcMesh );

private:
	struct StMaterial
	{
		U32								m_uVertexNum;
		CConstantBuffer*				m_pcConstantBuffer;
		CDirectXTexture*				m_pcTexture;
		
		void Init()
		{
			m_uVertexNum = 0;
			m_pcConstantBuffer = nullptr;
			m_pcTexture = nullptr;
		}
	};

private:
	ID3DBuffer*			m_pcVertexBuffer;
	ID3DBuffer*			m_pcIndexBuffer;

	U32					m_uMaterialNum;
	StMaterial*			m_pstMaterialArray;
};

#endif // #ifndef INCLUDE_LIB_MESH_MESHDRAWER_H