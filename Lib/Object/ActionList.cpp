/**
 * @file	CActiionList.cpp
 * @brief	Cactionクラスのリスト
 * @date	2015/02/01 22:07:49
 */

#include "Lib/LibPrecompile.h"

#include "Lib/Object/ActionList.h"
#include "Lib/Object/Action.h"

/**
 * @brief	コンストラクタ。
 */
CActionList::CActionList()
	: CSingleton<CActionList>()
	, m_stParam()
	, m_pcActionList( nullptr )
{
	m_stParam.Init();
}

/**
 * @brief	デストラクタ。
 */
CActionList::~CActionList()
{
	P_DELETE_ARRAY( m_pcActionList );
}

/**
 * @brief		初期化。
 * @param[in]	_rstParam	: 初期化用パラメータ。
 */
void CActionList::Init( const StInitParam& _rstParam )
{
	ASSERT( 0 < _rstParam.m_uLevelMax );
	if (_rstParam.m_uLevelMax <= 0)
	{
		return;	// failsafe
	}

	ASSERT( 0 < _rstParam.m_uLevelReserveSize );
	if (_rstParam.m_uLevelReserveSize <= 0)
	{
		return; // failsafe
	}

	MemCopy( &m_stParam, &_rstParam, sizeof( m_stParam ) );

	ASSERT( nullptr == m_pcActionList );
	P_DELETE_ARRAY( m_pcActionList );
	m_pcActionList = pnew CObjectList<CAction>[ m_stParam.m_uLevelMax ];

	for (U32 ii = 0; ii < m_stParam.m_uLevelMax; ++ii)
	{
		m_pcActionList[ ii ].GetList().reserve( m_stParam.m_uLevelReserveSize );
	}
}

/**
 * @brief		登録処理。
 * @param[in]	_pObjcet	: 登録するオブジェクト。
 */
void CActionList::Register( CAction* _pObject )
{
	ASSERT( _pObject );
	if ( nullptr == _pObject )
	{
		return;	// failsafe
	}

	const U32 uActLv = _pObject->GetActionLv();
	ASSERT( uActLv < m_stParam.m_uLevelMax );
	if (m_stParam.m_uLevelMax <= uActLv)
	{
		return;	// failsafe
	}

	ASSERT( m_pcActionList );
	if (nullptr == m_pcActionList)
	{
		return;	// failsafe
	}

	m_pcActionList[ uActLv ].Register( _pObject );
}

/**
 * @brief		解除処理。
 * @param[in]	_pObjcet	: 解除するオブジェクト。
 */
void CActionList::UnRegister( CAction* _pObject )
{
	ASSERT( _pObject );
	if ( nullptr == _pObject )
	{
		return;	// failsafe
	}

	const U32 uActLv = _pObject->GetActionLv();
	ASSERT( uActLv < m_stParam.m_uLevelMax );
	if (m_stParam.m_uLevelMax <= uActLv)
	{
		return;	// failsafe
	}

	ASSERT( m_pcActionList );
	if (nullptr == m_pcActionList)
	{
		return;	// failsafe
	}

	m_pcActionList[ uActLv ].UnRegister( _pObject );
}

/**
 * @brief		指定したレベルのアクションを実行。
 * @param[in]	_uActionLv	: 実行するアクションレベル。
 */
void CActionList::ExecAction( U32 _uActionLv )
{
	ASSERT( m_pcActionList );
	if (nullptr == m_pcActionList)
	{
		return;	// failsafe
	}

	ASSERT( _uActionLv < m_stParam.m_uLevelMax );
	if (m_stParam.m_uLevelMax <= _uActionLv)
	{
		return;	// failsafe
	}

	auto& rcList = m_pcActionList[ _uActionLv ].GetList();
	for (auto* pcAction : rcList )
	{
		if (pcAction)
		{
			if (pcAction->IsActionActive())
			{
				pcAction->Action();
			}
		}
	}
}

/**
 * @brief		ループ終了時に行いたい処理。
 */
void CActionList::LoopEndAct()
{
	ASSERT( m_pcActionList );
	if (nullptr == m_pcActionList)
	{
		return;	// failsafe
	}

	for (U32 ii = 0; ii < m_stParam.m_uLevelMax; ++ii)
	{
		m_pcActionList[ ii ].LoopEndAct();
	}
}
