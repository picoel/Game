/**
  * @file	DrawList.cpp
  * @brief	CDraw�N���X�̃��X�g�B
  * @data	2015/11/04 05:05:23
  */
#include "Lib/LibPrecompile.h"
#include "Lib/Object/DrawList.h"
#include "Lib/Object/Draw.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CDrawList::CDrawList()
	: CSingleton<CDrawList>()
	, m_stParam()
	, m_pcDrawList( nullptr )
{
	m_stParam.Init();
}

/**
 * @brief	�f�X�g���N�^�B
 */
CDrawList::~CDrawList()
{
	P_DELETE_ARRAY( m_pcDrawList );
}

/**
 * @brief		�������B
 * @param[in]	_rstParam	: �������p�p�����[�^�B
 */
void CDrawList::Init( const StInitParam& _rstParam )
{
	ASSERT( 0 < _rstParam.m_uLevelMax );
	if (_rstParam.m_uLevelMax <= 0)
	{
		return;	// failsafe
	}

	ASSERT( 0 < _rstParam.m_uLevelReserveSize );
	if (_rstParam.m_uLevelReserveSize <= 0)
	{
		return;	// failsafe
	}

	MemCopy( &m_stParam, &_rstParam, sizeof( m_stParam ) );

	ASSERT( nullptr == m_pcDrawList );
	P_DELETE_ARRAY( m_pcDrawList );
	m_pcDrawList = pnew CObjectList<CDraw>[ m_stParam.m_uLevelMax ];

	for (U32 ii = 0; ii < m_stParam.m_uLevelMax; ++ii)
	{
		m_pcDrawList[ ii ].GetList().reserve( m_stParam.m_uLevelReserveSize );
	}
}

/**
 * @brief		�o�^�����B
 * @param[in]	_pObject	: �o�^����I�u�W�F�N�g�B
 */
void CDrawList::Register( CDraw* _pObject )
{
	ASSERT( _pObject );
	if (nullptr == _pObject)
	{
		return;	// failsafe
	}

	const U32 uDrawLv = _pObject->GetDrawLv();
	ASSERT( uDrawLv < m_stParam.m_uLevelMax );
	if (m_stParam.m_uLevelMax <= uDrawLv)
	{
		return;	// failsafe
	}

	ASSERT( m_pcDrawList );
	if (nullptr == m_pcDrawList)
	{
		return;	// failsafe
	}

	m_pcDrawList[ uDrawLv ].Register( _pObject );
}

/**
 * @brief		���������B
 * @param[in]	_pObject	: ��������I�u�W�F�N�g�B
 */
void CDrawList::UnRegister( CDraw* _pObject )
{
	ASSERT( _pObject );
	if (nullptr == _pObject)
	{
		return;	// failsafe
	}

	const U32 uDrawLv = _pObject->GetDrawLv();
	ASSERT( uDrawLv < m_stParam.m_uLevelMax );
	if (m_stParam.m_uLevelMax <= uDrawLv)
	{
		return;	// failsafe
	}

	ASSERT( m_pcDrawList );
	if (nullptr == m_pcDrawList)
	{
		return;	// failsafe
	}

	m_pcDrawList[ uDrawLv ].UnRegister( _pObject );
}

/**
 * @brief		�w�肵�����x���̕`�揈�������s�B
 * @param[in]	_uDrawLv	: �`�惌�x���B
 */
void CDrawList::ExecDraw( U32 _uDrawLv, IRenderContext* _pcRenderContext )
{
	ASSERT( _pcRenderContext );
	if (nullptr == _pcRenderContext)
	{
		return;	// failsafe
	}

	ASSERT( m_pcDrawList );
	if (nullptr == m_pcDrawList)
	{
		return;	// failsafe
	}

	auto& rcList = m_pcDrawList[ _uDrawLv ].GetList();
	for (auto* pcDraw : rcList)
	{
		if (pcDraw)
		{
			if (pcDraw->IsActiveDraw())
			{
				pcDraw->Draw( _pcRenderContext );
			}
		}
	}
}

/**
 * @brief		���[�v�I�����ɍs�����������B
 */
void CDrawList::LoopEndAct()
{
	ASSERT( m_pcDrawList );
	if (nullptr == m_pcDrawList)
	{
		return;	// failsafe
	}

	for (U32 ii = 0; ii < m_stParam.m_uLevelMax; ++ii)
	{
		m_pcDrawList[ ii ].LoopEndAct();
	}
}
