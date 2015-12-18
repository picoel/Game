/**
  * @file	WinDirectX11.h
  * @brief	DirectX11を使用したウィンドウクラス。
  * @date 2015/05/03 19:12:24
  */

#ifndef INCLUDE_WINDIRECTX11_H
#define INCLUDE_WINDIRECTX11_H

#include "Windows/WinBase.h"

/*
 * @class	CWinDirectX11
 * @brief	DirectX11を使用したウィンドウクラス。
 */
class CWinDirectX11 
	: public CWinBase
{
public:
	/// コンストラクタ。
	CWinDirectX11( const StInitParam& _rstInitParam );
	/// デストラクタ。
	virtual ~CWinDirectX11();

	/// ウィンドウプロシージャ。
	virtual LRESULT WndProc( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam ) final;
};

#endif // #ifndef INCLUDE_WINDIRECTX11_H
