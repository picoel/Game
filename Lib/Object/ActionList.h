/**
 * @file	CActionList.h
 * @brief	CActionクラスのリスト。
 * @date	2014/12/26 09:40:53
 */

#ifndef INCLUDE_CACTIONLIST_H
#define INCLUDE_CACTIONLIST_H

class CAction;

#include "Lib/Thread/CriticalSection.h"
#include "Lib/Utility/Singleton.h"
#include "Lib/Object/ObjectList.h"

/**
 * @class	CActionList
 * @brief	CActionクラスのリスト。
 */
class CActionList : public CSingleton<CActionList>
{
	friend CSingleton < CActionList > ;
private:
	/// コンストラクタ。
	CActionList();

public:
	/// 初期化用構造体。
	struct StInitParam
	{
		U32 m_uLevelMax;			///< レベルの最大数。
		U32 m_uLevelReserveSize;	///< レベル毎の予約サイズ。

		void Init()
		{
			m_uLevelMax = 0;
			m_uLevelReserveSize = 0;
		}
	};

public:
	/// デストラクタ。
	virtual ~CActionList();

	/// 初期化。
	void Init( const StInitParam& _rstParam );

	/// 登録処理。
	void Register( CAction* _pObject );
	/// 解除処理。
	void UnRegister( CAction* _pObject );

	/// アクションを実行。
	void ExecAction( U32 _uActionLv );

	/// ループ終了時に行いたい処理。
	void LoopEndAct();

	/// 最大レベルを取得。
	U32 GetMaxLv() const{ return m_stParam.m_uLevelMax; }

private:
	StInitParam			m_stParam;

	CObjectList<CAction>*	m_pcActionList;
};

#endif // #ifndef INCLUDE_CACTIONLIST_H
