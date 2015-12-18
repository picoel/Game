/**
  * @file	Draw.cpp
  * @brief	描画を行う基底クラス。
  * @data 2015/11/04 05:00:18
  */

#include "Lib/LibPrecompile.h"
#include "Lib/Object/Draw.h"
#include "Lib/Object/DrawList.h"

/**
 * @brief	コンストラクタ。
 * @param	_uDrawLv	: 描画レベル。
 */
CDraw::CDraw( U32 _uDrawLv )
	: m_uDrawLv( _uDrawLv )
	, m_bActive( true )
{
	CDrawList* pcDrawList = CDrawList::GetInstance();
	ASSERT( pcDrawList );
	if (pcDrawList)
	{
		pcDrawList->Register( this );
	}
}

/**
 * @brief	デストラクタ。
 */
CDraw::~CDraw()
{
	CDrawList* pcDrawList = CDrawList::GetInstance();
	ASSERT( pcDrawList );
	if (pcDrawList)
	{
		pcDrawList->UnRegister( this );
	}

}