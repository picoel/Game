/**
  * @file	SequenceControl.h
  * @brief	シーケンス制御クラス。
  * @date 2015/09/02 03:35:09
  */

#ifndef INCLUDE_LIB_SEQUENCE_CONTROL_H
#define INCLUDE_LIB_SEQUENCE_CONTROL_H

#include "Lib/Utility/Singleton.h"

class CSequence;
class CSequenceFactory;
class IRenderContext;

/*
 * @class CSequenceControl
 * @brief シーケンスの制御クラス。
 */
class CSequenceControl
{
public:
	/// 初期化用パラメータ。
	struct StInitParam
	{
		CSequenceFactory*	m_pcFactory;
		U32					m_uStartSequenceID;

		void Init()
		{
			m_pcFactory = nullptr;
			m_uStartSequenceID = 0;
		}
	};

public:
	/// コンストラクタ。
	CSequenceControl( const StInitParam& _rstInitParam );

	/// デストラクタ。
	virtual ~CSequenceControl();

	/// フレーム開始時の処理。
	void LoopStartAct();
	/// アクションレベル毎の開始処理。
	void ActionLvInit( U32 _uActionLv );
	/// 描画レベル毎の開始処理。
	void DrawLvInit( U32 _uDrawLv, IRenderContext* _pcContext );
	/// フレーム終了時の処理。
	void LoopEndAct();

private:
	CSequence*			m_pcSequence;
	CSequenceFactory*	m_pcFactory;
};

#endif // #ifndef INCLUDE_LIB_SEQUENCE_CONTROL_H
