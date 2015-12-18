/**
  * @file	ObjectList.h
  * @brief	オブジェクトリスト。
  * @data 2015/11/04 05:16:38
  */

#ifndef INCLUDE_LIB_OBJECTLIST_H
#define INCLUDE_LIB_OBJECTLIST_H

#include "Lib/Utility/List.h"
#include "Lib/Thread/CriticalSection.h"

/*
 * @class	CObjectList
 * @brief	オブジェクトリスト。
 */
template< class T >
class CObjectList
{
public:
	/// コンストラクタ。
	CObjectList();
	/// デストラクタ。
	virtual ~CObjectList(){}

	void LoopEndAct();

	void Register( T* _pObj );
	void UnRegister( T* _pObj );

	CVector<T*>& GetList(){ return m_cObjArray; }

protected:
	CDeque<T*>		m_cObjWaitRegistArray;	///< 登録待ちリスト。
	CVector<T*>		m_cObjArray;

	CCriticalSection	m_cCriticalSection;
};

#include "Lib/Object/ObjectListDetail.h"

#endif // #ifndef INCLUDE_LIB_OBJECTLIST_H
