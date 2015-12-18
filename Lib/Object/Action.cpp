/**
  * @file	Action.cpp
  * @brief	Action���s�����N���X�B
  * @date	2015/05/23 03:09:39
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Object/Action.h"
#include "Lib/Object/ActionList.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_eActionLv	: �A�N�V�������x���B
 */
CAction::CAction( U32 _uActionLv )
	: m_uActionLv( _uActionLv )
	, m_bActive( true )
{
	auto* pcActionList = CActionList::GetInstance();
	ASSERT( pcActionList );
	if (pcActionList)
	{
		pcActionList->Register( this );
	}
}

/**
 * @brief	�f�X�g���N�^�B
 */
CAction::~CAction()
{
	auto* pcActionList = CActionList::GetInstance();
	ASSERT( pcActionList );
	if (pcActionList)
	{
		pcActionList->UnRegister( this );
	}
}
