/**
  * @file	SequenceControl.h
  * @brief	�V�[�P���X����N���X�B
  * @date 2015/09/02 03:35:09
  */

#ifndef INCLUDE_LIB_SEQUENCE_CONTROL_H
#define INCLUDE_LIB_SEQUENCE_CONTROL_H

#include "Lib/Utility/Singleton.h"

class CSequence;
class CSequenceFactory;
class IRenderContext;

/*
 * @class CSequenceControl
 * @brief �V�[�P���X�̐���N���X�B
 */
class CSequenceControl
{
public:
	/// �������p�p�����[�^�B
	struct StInitParam
	{
		CSequenceFactory*	m_pcFactory;
		U32					m_uStartSequenceID;

		void Init()
		{
			m_pcFactory = nullptr;
			m_uStartSequenceID = 0;
		}
	};

public:
	/// �R���X�g���N�^�B
	CSequenceControl( const StInitParam& _rstInitParam );

	/// �f�X�g���N�^�B
	virtual ~CSequenceControl();

	/// �t���[���J�n���̏����B
	void LoopStartAct();
	/// �A�N�V�������x�����̊J�n�����B
	void ActionLvInit( U32 _uActionLv );
	/// �`�惌�x�����̊J�n�����B
	void DrawLvInit( U32 _uDrawLv, IRenderContext* _pcContext );
	/// �t���[���I�����̏����B
	void LoopEndAct();

private:
	CSequence*			m_pcSequence;
	CSequenceFactory*	m_pcFactory;
};

#endif // #ifndef INCLUDE_LIB_SEQUENCE_CONTROL_H
