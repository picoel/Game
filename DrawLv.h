/**
  * @file	DrawLv.h
  * @brief	•`‰æƒŒƒxƒ‹‚Ì’è‹`B
  * @data 2015/11/08 08:56:55
  */

#ifndef INCLUDE_DRAW_LV_H
#define INCLUDE_DRAW_LV_H

class CDrawLv
{
public:
	enum class EnDrawLv : U32
	{
		Back = 0,
		Middle,
		Front,

		Max,
	};

public:
	static U32 Back(){ return s_cast<U32> ( EnDrawLv::Back ); }
	static U32 Middle(){ return s_cast<U32> ( EnDrawLv::Middle ); }
	static U32 Front(){ return s_cast<U32> ( EnDrawLv::Front ); }

	static U32 Max(){ return s_cast<U32> ( EnDrawLv::Max ); }
};

#endif // #ifndef INCLUDE_DRAW_LV_H