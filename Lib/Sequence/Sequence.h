/**
  * @file	Sequence.h
  * @brief	�V�[�P���X�B
  * @date 2015/09/02 03:24:41
  */
#ifndef INCLUDE_LIB_SEQUENCE_H
#define INCLUDE_LIB_SEQUENCE_H

/*
 * @class	CSequence
 * @brief	�V�[�P���X�N���X�B
 */
class CSequence
{
public:
	/// �R���X�g���N�^�B
	CSequence(){}
	/// �f�X�g���N�^�B
	virtual ~CSequence(){}

	/// �t���[���J�n���ɍs�������B
	virtual void LoopStartAct(){}
	/// �A�N�V�������x�����̏����������B
	virtual void ActionLvInit( U32 _uActionLv ){}
	/// �`�惌�x�����̏����������B
	virtual void DrawLvInit( U32 _uDrawLv, IRenderContext* _pcContext ){}
	/// �t���[���I�����ɍs�������B
	virtual void LoopEndAct(){}

	/// �V�[�P���X���I���������B
	virtual bool IsEnd () const = 0;

	/// ���̃V�[�P���X���擾�B
	virtual U32 GetNext() const = 0;
};

#endif // #ifndef INCLUDE_LIB_SEQUENCE_H
