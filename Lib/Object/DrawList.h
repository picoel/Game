/**
  * @file	DrawList.h
  * @brief	CDrawクラスのリスト。
  * @data	2015/11/04 05:05:23
  */

#ifndef INCLUDE_LIB_DRAWLIST_H
#define INCLUDE_LIB_DRAWLIST_H

class CDraw;
class IRenderContext;

#include "Lib/Thread/CriticalSection.h"
#include "Lib/Utility/Singleton.h"
#include "Lib/Object/ObjectList.h"

/*
 * @class CDrawList
 * @brief CDrawクラスのリスト。
 */
class CDrawList : public CSingleton<CDrawList>
{
	friend CSingleton< CDrawList >;

private:
	CDrawList();

public:
	/// 初期化用構造体。
	struct StInitParam
	{
		U32	m_uLevelMax;			///< レベルの最大数。
		U32 m_uLevelReserveSize;	///< レベルごとの予約サイズ。

		void Init()
		{
			m_uLevelMax = 0;
			m_uLevelReserveSize = 0;
		}
	};

public:
	virtual ~CDrawList();

	void Init( const StInitParam& _rstParam );

	void Register( CDraw* _pObject );
	void UnRegister( CDraw* _pObject );

	void ExecDraw( U32 _uDrawLv, IRenderContext* _pcRenderContext );

	void LoopEndAct();

	U32 GetMaxLv() const{ return m_stParam.m_uLevelMax; }

protected:
	StInitParam				m_stParam;
	CObjectList< CDraw >*	m_pcDrawList;
};

#endif // #ifndef INCLUDE_LIB_DRAWLIST_H