/**
  * @file  InitSequence.h
  * @brief �Q�[���̏������p�V�[�P���X�B
  * @date 2015/09/02 05:05:46
  */

#ifndef INCLUDE_TITLE_INIT_SEQUENCE_H
#define INCLUDE_TITLE_INIT_SEQUENCE_H

/*
 * @class CInitSequence
 * @brief �������p�V�[�P���X�B
 */
class CInitSequence : public CSequence
{
public:
	/// �R���X�g���N�^�B
	CInitSequence()
		: CSequence()
		, m_pcPMDReader( nullptr )
		, m_pcMesh( nullptr )
		, m_pcMeshDrawer( nullptr )
	{
		m_pcPMDReader = pnew CPMDReader( "./Blanc/Blanc.pmd" );
	}

	/// �f�X�g���N�^�B
	virtual ~CInitSequence()
	{
		P_DELETE( m_pcPMDReader );
		P_DELETE( m_pcMesh );
		P_DELETE( m_pcMeshDrawer );
	}

	/// �t���[���J�n���̏����B
	void LoopStartAct() override
	{
		if (m_pcPMDReader->IsReadEnd())
		{
			if (nullptr == m_pcMesh)
			{
				m_pcMesh = pnew CPMDMesh( *m_pcPMDReader );
				m_pcMeshDrawer = pnew CMeshDrawer( m_pcMesh );
			}
		}
	}

	/// �t���[���I�����̏����B
	void LoopEndAct() override
	{
	}

	/// �I���������B
	bool IsEnd() const override
	{
		return false;
	}
	
	/// ���̃V�[�P���X���擾�B
	U32 GetNext() const override
	{
		return s_cast<U32>( EnSequenceID::enInit );
	}

private:
	CPMDReader*		m_pcPMDReader;
	CPMDMesh*		m_pcMesh;
	CMeshDrawer*	m_pcMeshDrawer;
};

#endif // #ifndef INCLUDE_TITLE_INIT_SEQUENCE_H