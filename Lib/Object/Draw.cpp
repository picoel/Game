/**
  * @file	Draw.cpp
  * @brief	�`����s�����N���X�B
  * @data 2015/11/04 05:00:18
  */

#include "Lib/LibPrecompile.h"
#include "Lib/Object/Draw.h"
#include "Lib/Object/DrawList.h"

/**
 * @brief	�R���X�g���N�^�B
 * @param	_uDrawLv	: �`�惌�x���B
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
 * @brief	�f�X�g���N�^�B
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