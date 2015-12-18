/**
  * @file	SequenceFactory.h
  * @brief	シーケンス生成クラス。
  * @date 2015/09/02 03:45:54
  */

#ifndef INCLUDE_LIB_SEQUENCE_FACTORY_H
#define INCLUDE_LIB_SEQUENCE_FACTORY_H

class CSequence;

/*
 * @class CSequenceFactory
 * @brief シーケンス生成クラス。
 */
class CSequenceFactory
{
public:
	/// コンストラクタ。
	CSequenceFactory(){}
	/// デストラクタ。
	virtual ~CSequenceFactory(){}

	/// シーケンスのインスタンス生成。
	virtual CSequence* CreateInstance( U32 _uSequenceID ){ return nullptr; }
};

#endif // #ifndef INCLUDE_LIB_SEQUENCE_FACTORY_H
