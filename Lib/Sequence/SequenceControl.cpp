/**
  * @file	SequenceControl.cpp
  * @brief	シーケンス制御クラス。
  * @date 2015/09/02 03:35:09
  */
#include "Lib/LibPrecompile.h"

#include "Lib/Sequence/SequenceControl.h"
#include "Lib/Sequence/Sequence.h"
#include "Lib/Sequence/SequenceFactory.h"

/**
 * @brief	コンストラクタ。
 * @param	_rstInitParam	: 初期化用パラメータ。
 */
CSequenceControl::CSequenceControl( const StInitParam& _rstInitParam )
	: m_pcSequence( nullptr )
	, m_pcFactory( nullptr )
{
	ASSERT( _rstInitParam.m_pcFactory );
	if (nullptr == _rstInitParam.m_pcFactory)
	{
		return;	// failsafe
	}

	m_pcFactory = _rstInitParam.m_pcFactory;
	m_pcSequence = m_pcFactory->CreateInstance( _rstInitParam.m_uStartSequenceID );
}

/**
 * @brief	デストラクタ。
 */
CSequenceControl::~CSequenceControl()
{
	P_DELETE( m_pcSequence );
	P_DELETE( m_pcFactory );
}

/**
 * @brief	フレーム開始時の処理
 */
void CSequenceControl::LoopStartAct()
{
	ASSERT( m_pcSequence );
	if (nullptr == m_pcSequence)
	{
		return; // failsafe
	}

	m_pcSequence->LoopStartAct();
}

/**
 * @brief		アクションレベル毎の開始処理。
 * @param[in]	_uActionLv	: 開始するアクションレベル。
 */
void CSequenceControl::ActionLvInit( U32 _uActionLv )
{
	ASSERT( m_pcSequence );
	if (nullptr == m_pcSequence)
	{
		return; // failsafe
	}

	m_pcSequence->ActionLvInit( _uActionLv );
}

/**
 * @brief		描画レベル毎の開始処理。
 * @param[in]	_uDrawLv	: 開始する描画レベル。
 * @param[in]	_pcContext	: 描画コンテキスト。
 */
void CSequenceControl::DrawLvInit( U32 _uDrawLv, IRenderContext* _pcContext )
{
	ASSERT( m_pcSequence );
	if (nullptr == m_pcSequence)
	{
		return; // failsafe
	}

	m_pcSequence->DrawLvInit( _uDrawLv, _pcContext );

}

/**
 * @brief	フレーム終了時の処理。
 */
void CSequenceControl::LoopEndAct()
{
	ASSERT( m_pcSequence );
	if (nullptr == m_pcSequence)
	{
		return;	// failsafe
	}

	ASSERT( m_pcFactory );
	if ( nullptr == m_pcFactory)
	{
		return;	// failsafe
	}

	m_pcSequence->LoopEndAct();

	if (m_pcSequence->IsEnd())
	{
		const U32 uNextSequenceID = m_pcSequence->GetNext();

		P_DELETE( m_pcSequence );
		m_pcSequence = m_pcFactory->CreateInstance( uNextSequenceID );
	}
}
