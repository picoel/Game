/**
  * @file	SequenceControl.cpp
  * @brief	�V�[�P���X����N���X�B
  * @date 2015/09/02 03:35:09
  */
#include "Lib/LibPrecompile.h"

#include "Lib/Sequence/SequenceControl.h"
#include "Lib/Sequence/Sequence.h"
#include "Lib/Sequence/SequenceFactory.h"

/**
 * @brief	�R���X�g���N�^�B
 * @param	_rstInitParam	: �������p�p�����[�^�B
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
 * @brief	�f�X�g���N�^�B
 */
CSequenceControl::~CSequenceControl()
{
	P_DELETE( m_pcSequence );
	P_DELETE( m_pcFactory );
}

/**
 * @brief	�t���[���J�n���̏���
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
 * @brief		�A�N�V�������x�����̊J�n�����B
 * @param[in]	_uActionLv	: �J�n����A�N�V�������x���B
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
 * @brief		�`�惌�x�����̊J�n�����B
 * @param[in]	_uDrawLv	: �J�n����`�惌�x���B
 * @param[in]	_pcContext	: �`��R���e�L�X�g�B
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
 * @brief	�t���[���I�����̏����B
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
