/**
  * @file	ObjectListDetail.h
  * @brief	�I�u�W�F�N�g���X�g�̎����B
  * @data 2015/11/04 05:16:38
  */

#include "Lib/Object/ObjectList.h"

#ifndef INCLUDE_LIB_OBJECTLIST_DETAIL_H
#define INCLUDE_LIB_OBJECTLIST_DETAIL_H

/**
 * @brief		�R���X�g���N�^�B
 */
template< class T >
CObjectList<T>::CObjectList()
	: m_cObjWaitRegistArray()
	, m_cObjArray()
	, m_cCriticalSection()
{
}

/**
 * @brief	���[�v�I�����̏����B
 */
template< class T >
void CObjectList<T>::LoopEndAct()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	// �폜���ꂽ�I�u�W�F�N�g�����X�g����O���B
	auto cItBegin = m_cObjArray.begin();
	auto cItEnd = m_cObjArray.end();
	auto cItBeginRemove = std::remove_if( cItBegin, cItEnd,
		[]( T* _pcObj )->bool{ return nullptr == _pcObj; } );
	m_cObjArray.erase( cItBeginRemove, cItEnd );

	// �L���[�ɒǉ����ꂽ�A�N�V������ǉ��B
	while (!m_cObjWaitRegistArray.empty())
	{
		auto* pcObj = m_cObjWaitRegistArray.front();
		m_cObjWaitRegistArray.pop_front();
		ASSERT( pcObj );
		if (nullptr != pcObj)
		{
			m_cObjArray.push_back( pcObj );
		}
	}
}

/**
 * @brief	�I�u�W�F�N�g��o�^�B
 * @param	_pObj	: �o�^����I�u�W�F�N�g�B
 */
template< class T >
void CObjectList<T>::Register( T* _pObj )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
	ASSERT( _pObj );
	if (nullptr == _pObj)
	{
		return;	// failsafe
	}

	m_cObjWaitRegistArray.push_back( _pObj );
}

/**
 * @brief	�I�u�W�F�N�g�̓o�^����������B
 * @param	_pObj	: ��������I�u�W�F�N�g�B
 */
template< class T >
void CObjectList<T>::UnRegister( T* _pObj )
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	auto cItBegin = m_cObjArray.begin();
	auto cItEnd = m_cObjArray.end();
	auto cIt = std::find( cItBegin, cItEnd, _pObj );
	if (cIt != cItEnd)
	{
		*cIt = nullptr;
	}
	else
	{
		// �o�^�҂����X�g�ɓo�^����Ă���\��������B
		auto cItWaitBegin = m_cObjWaitRegistArray.begin();
		auto cItWaitEnd = m_cObjWaitRegistArray.end();
		auto cItWaitFind = std::find( cItWaitBegin, cItWaitEnd, _pObj );

		// �����Ō�����Ȃ���Ζ��o�^�̃I�u�W�F�N�g���n���ꂽ���ɂȂ�B
		ASSERT( cItWaitFind != cItWaitEnd );
		if (cItWaitFind != cItWaitEnd)
		{
			m_cObjWaitRegistArray.erase( cItWaitFind, cItWaitEnd );
		}
	}
}

#endif // #ifndef INCLUDE_LIB_OBJECTLIST_DETAIL_H
