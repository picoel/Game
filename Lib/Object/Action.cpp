/**
  * @file	Action.cpp
  * @brief	Actionを行う基底クラス。
  * @date	2015/05/23 03:09:39
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Object/Action.h"
#include "Lib/Object/ActionList.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_eActionLv	: アクションレベル。
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
 * @brief	デストラクタ。
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
