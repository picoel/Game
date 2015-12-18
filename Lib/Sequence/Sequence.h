/**
  * @file	Sequence.h
  * @brief	シーケンス。
  * @date 2015/09/02 03:24:41
  */
#ifndef INCLUDE_LIB_SEQUENCE_H
#define INCLUDE_LIB_SEQUENCE_H

/*
 * @class	CSequence
 * @brief	シーケンスクラス。
 */
class CSequence
{
public:
	/// コンストラクタ。
	CSequence(){}
	/// デストラクタ。
	virtual ~CSequence(){}

	/// フレーム開始時に行う処理。
	virtual void LoopStartAct(){}
	/// アクションレベル毎の初期化処理。
	virtual void ActionLvInit( U32 _uActionLv ){}
	/// 描画レベル毎の初期化処理。
	virtual void DrawLvInit( U32 _uDrawLv, IRenderContext* _pcContext ){}
	/// フレーム終了時に行う処理。
	virtual void LoopEndAct(){}

	/// シーケンスが終了したか。
	virtual bool IsEnd () const = 0;

	/// 次のシーケンスを取得。
	virtual U32 GetNext() const = 0;
};

#endif // #ifndef INCLUDE_LIB_SEQUENCE_H
