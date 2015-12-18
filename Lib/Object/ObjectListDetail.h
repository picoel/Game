/**
  * @file	ObjectListDetail.h
  * @brief	オブジェクトリストの実装。
  * @data 2015/11/04 05:16:38
  */

#include "Lib/Object/ObjectList.h"

#ifndef INCLUDE_LIB_OBJECTLIST_DETAIL_H
#define INCLUDE_LIB_OBJECTLIST_DETAIL_H

/**
 * @brief		コンストラクタ。
 */
template< class T >
CObjectList<T>::CObjectList()
	: m_cObjWaitRegistArray()
	, m_cObjArray()
	, m_cCriticalSection()
{
}

/**
 * @brief	ループ終了時の処理。
 */
template< class T >
void CObjectList<T>::LoopEndAct()
{
	CCriticalSectionBlock cCSBlock( &m_cCriticalSection );

	// 削除されたオブジェクトをリストから外す。
	auto cItBegin = m_cObjArray.begin();
	auto cItEnd = m_cObjArray.end();
	auto cItBeginRemove = std::remove_if( cItBegin, cItEnd,
		[]( T* _pcObj )->bool{ return nullptr == _pcObj; } );
	m_cObjArray.erase( cItBeginRemove, cItEnd );

	// キューに追加されたアクションを追加。
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
 * @brief	オブジェクトを登録。
 * @param	_pObj	: 登録するオブジェクト。
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
 * @brief	オブジェクトの登録を解除する。
 * @param	_pObj	: 解除するオブジェクト。
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
		// 登録待ちリストに登録されている可能性がある。
		auto cItWaitBegin = m_cObjWaitRegistArray.begin();
		auto cItWaitEnd = m_cObjWaitRegistArray.end();
		auto cItWaitFind = std::find( cItWaitBegin, cItWaitEnd, _pObj );

		// ここで見つからなければ未登録のオブジェクトが渡された事になる。
		ASSERT( cItWaitFind != cItWaitEnd );
		if (cItWaitFind != cItWaitEnd)
		{
			m_cObjWaitRegistArray.erase( cItWaitFind, cItWaitEnd );
		}
	}
}

#endif // #ifndef INCLUDE_LIB_OBJECTLIST_DETAIL_H
