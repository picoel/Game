/**
  * @file	WinBase.h
  * @brief	ウィンドウベースクラス。
  * @date 2015/04/24 00:10:34
  */

#ifndef INCLUDE_WINBASE_H
#define INCLUDE_WINBASE_H

/*
 * @class	CWinBase
 * @brief	ウィンドウのベースクラス。
 */
class CWinBase
{
public:
	/// 初期化用パラメータ。
	struct StInitParam
	{
		HINSTANCE	m_hInstance;		///< アプリケーションハンドル。
		S32			m_sCmdShow;			///< 表示方法。
		U32			m_uClassStyle;		///< ウィンドウクラススタイル。
		U32			m_uWindowStyle;		///< ウィンドウスタイル。
		HICON		m_hIcon;			///< アイコンハンドル。
		HICON		m_hIconSm;			///< アイコンハンドル(小)。
		S32			m_sPosX;			///< 初期位置(X)。
		S32			m_sPosY;			///< 初期位置(Y)。
		S32			m_sWidth;			///< ウィンドウの幅。
		S32			m_sHeight;			///< ウィンドウの高さ。
		LPCTSTR		m_psClassName;		///< クラス名。
		LPCTSTR		m_psWindowName;		///< ウィンドウ名。

		void Init()
		{
			m_hInstance = NULL;
			m_sCmdShow = 0;
			m_uClassStyle = CS_HREDRAW | CS_VREDRAW;
			m_uWindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			m_hIcon = NULL;
			m_hIconSm = NULL;
			m_sPosX = 0;
			m_sPosY = 0;
			m_sWidth = 0;
			m_sHeight = 0;
			m_psClassName = nullptr;
			m_psWindowName = nullptr;
		}
	};

public:
	/// コンストラクタ。
	CWinBase( const StInitParam& _rstInitParam );
	/// デストラクタ。
	virtual ~CWinBase(){}

	/// ウィンドウの初期化。
	bool InitWindow();

	/// ウィンドウプロシージャ。
	static LRESULT CALLBACK WndProcWrapper( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam );
	virtual LRESULT WndProc( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam );

	/// ウィンドウの幅を取得。
	S32 GetWidth() const{ return m_stInitParam.m_sWidth; }
	/// ウィンドウの高さを取得。
	S32 GetHeight() const{ return m_stInitParam.m_sHeight; }

	/// ウィンドウハンドルを取得。
	HWND GetWindowHandle() const{ return m_hWnd; }

protected:
	StInitParam	m_stInitParam;	///< 初期化用パラメータ。
	CTString	m_cClassName;	///< クラス名。
	CTString		m_cWindowName;	///< ウィンドウ名。

	HWND		m_hWnd;
};

#endif // #ifndef INCLUDE_WINBASE_H 