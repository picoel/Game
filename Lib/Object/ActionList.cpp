/**
 * @file	CActiionList.cpp
 * @brief	Caction�N���X�̃��X�g
 * @date	2015/02/01 22:07:49
 */

#include "Lib/LibPrecompile.h"

#include "Lib/Object/ActionList.h"
#include "Lib/Object/Action.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CActionList::CActionList()
	: CSingleton<CActionList>()
	, m_stParam()
	, m_pcActionList( nullptr )
{
	m_stParam.Init();
}

/**
 * @brief	�f�X�g���N�^�B
 */
CActionList::~CActionList()
{
	P_DELETE_ARRAY( m_pcActionList );
}

/**
 * @brief		�������B
 * @param[in]	_rstParam	: �������p�p�����[�^�B
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
 * @brief		�o�^�����B
 * @param[in]	_pObjcet	: �o�^����I�u�W�F�N�g�B
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
 * @brief		���������B
 * @param[in]	_pObjcet	: ��������I�u�W�F�N�g�B
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
 * @brief		�w�肵�����x���̃A�N�V���������s�B
 * @param[in]	_uActionLv	: ���s����A�N�V�������x���B
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
 * @brief		���[�v�I�����ɍs�����������B
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
