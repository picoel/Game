/**
  * @file	Rect.h
  * @brief	矩形クラス。
  * @date 2015/09/10 04:35:58
  */

#ifndef INCLUDE_LIB_RECT_H
#define INCLUDE_LIB_RECT_H

/*
 * @class CRect
 * @brief 矩形クラス。
 */
class CRect
{
public:
	/// コンストラクタ。
	CRect();

	/// デストラクタ。
	virtual ~CRect(){}

	/// 中心座標を設定。
	void SetPos( F32 _fPosX, F32 _fPosY );
	/// 中心座標を取得。
	void GetPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 左上座標を設定。(現在の幅と高さに準じます。)
	void SetLeftUpPos( F32 _fPosX, F32 _fPosY );
	/// 左上座標を取得。(現在の幅と高さに準じます。)
	void GetLeftUpPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 中央上座標を設定。(現在の幅と高さに準じます。)
	void SetCenterUpPos( F32 _fPosX, F32 _fPosY );
	/// 中央上座標を取得。(現在の幅と高さに準じます。)
	void GetCenterUpPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 右上座標を設定。(現在の幅と高さに準じます。)
	void SetRightUpPos( F32 _fPosX, F32 _fPosY );
	/// 右上座標を取得。(現在の幅と高さに準じます。)
	void GetRightUpPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 左中央座標を設定。(現在の幅と高さに準じます。)
	void SetLeftCenterPos( F32 _fPosX, F32 _fPosY );
	/// 左中央座標を取得。(現在の幅と高さに準じます。)
	void GetLeftCenterPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 右中央座標を設定。(現在の幅と高さに準じます。)
	void SetRightCenterPos( F32 _fPosX, F32 _fPosY );
	/// 右中央座標を取得。(現在の幅と高さに準じます。)
	void GetRightCenterPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 左下座標を設定。(現在の幅と高さに準じます。)
	void SetLeftDownPos( F32 _fPosX, F32 _fPosY );
	/// 左下座標を取得。(現在の幅と高さに準じます。)
	void GetLeftDownPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 中央下座標を設定。(現在の幅と高さに準じます。)
	void SetCenterDownPos( F32 _fPosX, F32 _fPosY );
	/// 中央下座標を取得。(現在の幅と高さに準じます。)
	void GetCenterDownPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 右下座標を設定。(現在の幅と高さに準じます。)
	void SetRightDownPos( F32 _fPosX, F32 _fPosY );
	/// 右下座標を取得。(現在の幅と高さに準じます。)
	void GetRightDownPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// 幅を設定。
	void SetWidth( F32 _fWidth );
	/// 幅を取得。
	F32 GetWidth() const;
	/// 高さを設定。
	void SetHeight( F32 _fHeight );
	/// 高さを取得。
	F32 GetHeight() const;

private:
	F32	m_fPosX;
	F32	m_fPosY;
	F32	m_fWidth;
	F32	m_fHeight;
};

#endif // #ifndef INCLUDE_LIB_RECT_H
