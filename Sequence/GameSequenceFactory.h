/**
  * @file	GameSequenceFactory.h
  * @brief	ゲーム用シーケンス生成クラス。
  * @date 2015/09/02 04:54:39
  */

#ifndef INCLUDE_GAME_SEQUENCE_FACTORY_H
#define INCLUDE_GAME_SEQUENCE_FACTORY_H

/*
 * @class CGameSequenceFactory
 * @brief ゲーム用シーケンス生成クラス。
 */
class CGameSequenceFactory : public CSequenceFactory
{
public:
	/// コンストラクタ。
	CGameSequenceFactory(){}
	/// デストラクタ。
	virtual ~CGameSequenceFactory(){}

	/// シーケンスを生成。
	virtual CSequence* CreateInstance( U32 _uSequenceID ) override;
};

#endif // #ifndef INCLUDE_GAME_SEQUENCE_FACTORY_H