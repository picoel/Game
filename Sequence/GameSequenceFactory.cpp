/**
  * @file	GameSequenceFactory.cpp
  * @brief	�Q�[���p�V�[�P���X�����N���X�B
  * @date 2015/09/02 04:54:39
  */
#include "PreCompileHeader.h"

#include "Sequence/GameSequenceFactory.h"
#include "Sequence/SequenceID.h"

#include "Title/InitSequence.h"

/**
 * @brief		�V�[�P���X���쐬�B
 * @param[in]	_uSequenceID	: �V�[�P���XID( EnSequenceID )
 * @retval		�V�[�P���X�̃C���X�^���X�B
 */
CSequence* CGameSequenceFactory::CreateInstance( U32 _uSequenceID )
{
	const EnSequenceID eSequenceID = s_cast<EnSequenceID>( _uSequenceID );

	CSequence* pcRet = nullptr;
	switch (eSequenceID)
	{
	case EnSequenceID::enInit:
		pcRet = pnew CInitSequence();
		break;

	default:
		ASSERT( !"Invaild case" );
		break;
	}

	return pcRet;
}
