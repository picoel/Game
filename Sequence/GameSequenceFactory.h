/**
  * @file	GameSequenceFactory.h
  * @brief	�Q�[���p�V�[�P���X�����N���X�B
  * @date 2015/09/02 04:54:39
  */

#ifndef INCLUDE_GAME_SEQUENCE_FACTORY_H
#define INCLUDE_GAME_SEQUENCE_FACTORY_H

/*
 * @class CGameSequenceFactory
 * @brief �Q�[���p�V�[�P���X�����N���X�B
 */
class CGameSequenceFactory : public CSequenceFactory
{
public:
	/// �R���X�g���N�^�B
	CGameSequenceFactory(){}
	/// �f�X�g���N�^�B
	virtual ~CGameSequenceFactory(){}

	/// �V�[�P���X�𐶐��B
	virtual CSequence* CreateInstance( U32 _uSequenceID ) override;
};

#endif // #ifndef INCLUDE_GAME_SEQUENCE_FACTORY_H