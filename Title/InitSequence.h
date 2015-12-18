/**
  * @file  InitSequence.h
  * @brief ゲームの初期化用シーケンス。
  * @date 2015/09/02 05:05:46
  */

#ifndef INCLUDE_TITLE_INIT_SEQUENCE_H
#define INCLUDE_TITLE_INIT_SEQUENCE_H

/*
 * @class CInitSequence
 * @brief 初期化用シーケンス。
 */
class CInitSequence : public CSequence
{
public:
	/// コンストラクタ。
	CInitSequence()
		: CSequence()
		, m_pcPMDReader( nullptr )
		, m_pcMesh( nullptr )
		, m_pcMeshDrawer( nullptr )
	{
		m_pcPMDReader = pnew CPMDReader( "./Blanc/Blanc.pmd" );
	}

	/// デストラクタ。
	virtual ~CInitSequence()
	{
		P_DELETE( m_pcPMDReader );
		P_DELETE( m_pcMesh );
		P_DELETE( m_pcMeshDrawer );
	}

	/// フレーム開始時の処理。
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

	/// フレーム終了時の処理。
	void LoopEndAct() override
	{
	}

	/// 終了したか。
	bool IsEnd() const override
	{
		return false;
	}
	
	/// 次のシーケンスを取得。
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