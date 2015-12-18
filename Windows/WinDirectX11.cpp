/**
  * @file	WinDirectX11.cpp
  * @brief	DirectX11を使用したウィンドウクラス。
  * @date 2015/05/03 19:12:24
  */

#include "PreCompileHeader.h"
#include "Windows/WinDirectX11.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_rstInitParam	: 初期化用パラメータ。
 */
CWinDirectX11::CWinDirectX11( const StInitParam& _rstInitParam )
	: CWinBase( _rstInitParam )
{
}

/**
 * @brief	デストラクタ。
 */
CWinDirectX11::~CWinDirectX11()
{
}

/**
 * @brief		ウィンドウプロシージャ。
 * @param[in]	_hWnd		: ウィンドウハンドル。
 * @param[in]	_uMsg		: メッセージ。
 * @param[in]	_uWParam	: パラメータ。
 * @param[in]	_uLParam	: パラメータ。
 * @retval		LRESULT		: 処理結果。
 */
LRESULT CWinDirectX11::WndProc( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam )
{
	LRESULT uRet = 0;
	switch (_uMsg)
	{
	// キーの押下。
	case WM_KEYDOWN:
		// ESCAPEキーの押下でウィンドウ終了。
		if (VK_ESCAPE == _uWParam)
		{
			PostQuitMessage( 0 );
			uRet = 0;
		}
		break;

	default:
		uRet = CWinBase::WndProc( _hWnd, _uMsg, _uWParam, _uLParam );
		break;
	}

	return uRet;
}
