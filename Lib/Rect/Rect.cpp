/**
  * @file	Rect.cpp
  * @brief	矩形クラス。
  * @date 2015/09/10 04:35:58
  */

#include "lib/LibPrecompile.h"

#include "Lib/Rect/Rect.h"

/**
 * @brief	コンストラクタ。
 */
CRect::CRect()
	: m_fPosX( 0.0f )
	, m_fPosY( 0.0f )
	, m_fWidth( 0.0f )
	, m_fHeight( 0.0f )
{
}

/**
 * @brief		中心座標を設定。
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetPos( F32 _fPosX, F32 _fPosY )
{
	m_fPosX = _fPosX;
	m_fPosY = _fPosY;
}

/**
 * @brief		中心座標を取得。
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX;
	*_pfPosY = m_fPosY;
}

/**
 * @brief		左上座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetLeftUpPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX + m_fWidth * 0.5f, _fPosY + m_fHeight * 0.5f );
}

/**
 * @brief		左上座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetLeftUpPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX - m_fWidth * 0.5f;
	*_pfPosY = m_fPosY - m_fHeight * 0.5f;
}

/**
 * @brief		中央上座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetCenterUpPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX, _fPosY + m_fHeight * 0.5f );
}

/**
 * @brief		中央上座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetCenterUpPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX;
	*_pfPosY = m_fPosY - m_fHeight * 0.5f;
}

/**
 * @brief		右上座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetRightUpPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX - m_fWidth * 0.5f, _fPosY + m_fHeight * 0.5f );
}

/**
 * @brief		右上座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetRightUpPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX + m_fWidth * 0.5f;
	*_pfPosY = m_fPosY - m_fHeight * 0.5f;
}

/**
 * @brief		左中央座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetLeftCenterPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX + m_fWidth * 0.5f, _fPosY );
}

/**
 * @brief		左中央座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetLeftCenterPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX - m_fWidth * 0.5f;
	*_pfPosY = m_fPosY;
}

/**
 * @brief		右中央座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetRightCenterPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX - m_fWidth * 0.5f, _fPosY );
}

/**
 * @brief		右中央座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetRightCenterPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX + m_fWidth * 0.5f;
	*_pfPosY = m_fPosY;
}

/**
 * @brief		左下座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetLeftDownPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX + m_fWidth * 0.5f, _fPosY - m_fHeight * 0.5f );
}

/**
 * @brief		左下座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetLeftDownPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX - m_fWidth * 0.5f;
	*_pfPosY = m_fPosY + m_fHeight * 0.5f;
}

/**
 * @brief		中央下座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetCenterDownPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX, _fPosY - m_fHeight * 0.5f );
}

/**
 * @brief		中央下座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetCenterDownPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX;
	*_pfPosY = m_fPosY + m_fHeight * 0.5f;
}

/**
 * @brief		右下座標を設定。(現在の幅と高さに準じます。)
 * @param[in]	_fPosX	: X座標。
 * @param[in]	_fPosY	: Y座標。
 */
void CRect::SetRightDownPos( F32 _fPosX, F32 _fPosY )
{
	// 中心座標に変換。
	SetPos( _fPosX - m_fWidth * 0.5f, _fPosY - m_fHeight * 0.5f );
}

/**
 * @brief		右下座標を取得。(現在の幅と高さに準じます。)
 * @param[out]	_pfPosX	: X座標の格納先。
 * @param[out]	_pfPosY	: Y座標の格納先。
 */
void CRect::GetRightDownPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX + m_fWidth * 0.5f;
	*_pfPosY = m_fPosY + m_fHeight * 0.5f;
}

/**
 * @brief		幅を設定。
 * @param[in]	_fWidth	: 幅。
 */
void CRect::SetWidth( F32 _fWidth )
{
	m_fWidth = _fWidth;
}

/**
 * @brief		幅を取得。
 * @retval		F32	: 幅。
 */
F32 CRect::GetWidth() const
{
	return m_fWidth;
}

/**
 * @brief		高さを設定。
 * @param[in]	_fHeight	: 高さ。
 */
void CRect::SetHeight( F32 _fHeight )
{
	m_fHeight = _fHeight;
}

/**
 * @brief		高さを取得。
 * @retval		F32	: 高さ。
 */
F32 CRect::GetHeight() const
{
	return m_fHeight;
}