/**
  * @file	GameSequenceFactory.cpp
  * @brief	ゲーム用シーケンス生成クラス。
  * @date 2015/09/02 04:54:39
  */
#include "PreCompileHeader.h"

#include "Sequence/GameSequenceFactory.h"
#include "Sequence/SequenceID.h"

#include "Title/InitSequence.h"

/**
 * @brief		シーケンスを作成。
 * @param[in]	_uSequenceID	: シーケンスID( EnSequenceID )
 * @retval		シーケンスのインスタンス。
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
