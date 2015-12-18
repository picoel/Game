/**
  * @file	ActionLv.h
  * @brief	アクションレベルの定義。
  * @date 2015/05/23 03:02:12
  */

#ifndef INCLUDE_ACTION_LV_H
#define INCLUDE_ACTION_LV_H

class CActionLv
{
public:
	enum class EnActionLv : U32
	{
		System = 0,
		Normal,

		Max
	};

public:
	static U32 System(){ return s_cast<U32>(EnActionLv::System); }
	static U32 Normaml(){ return s_cast<U32>(EnActionLv::Normal); }
	static U32 Max(){ return s_cast<U32>(EnActionLv::Max); }
};

typedef CActionLv::EnActionLv	EnActLv;

#endif // #ifndef INCLUDE_ACTION_LV_H
