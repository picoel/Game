/**
  * @file	SequenceFactory.h
  * @brief	�V�[�P���X�����N���X�B
  * @date 2015/09/02 03:45:54
  */

#ifndef INCLUDE_LIB_SEQUENCE_FACTORY_H
#define INCLUDE_LIB_SEQUENCE_FACTORY_H

class CSequence;

/*
 * @class CSequenceFactory
 * @brief �V�[�P���X�����N���X�B
 */
class CSequenceFactory
{
public:
	/// �R���X�g���N�^�B
	CSequenceFactory(){}
	/// �f�X�g���N�^�B
	virtual ~CSequenceFactory(){}

	/// �V�[�P���X�̃C���X�^���X�����B
	virtual CSequence* CreateInstance( U32 _uSequenceID ){ return nullptr; }
};

#endif // #ifndef INCLUDE_LIB_SEQUENCE_FACTORY_H
