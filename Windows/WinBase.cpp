/**
  * @file	WinBase.h
  * @brief	ウィンドウベースクラス。
  * @date 2015/05/02 02:47:45
  */

#include "PreCompileHeader.h"
#include "Windows\WinBase.h"

/**
 * @brief		コンストラクタ。
 * @param[in]	_rstInitParam	: 初期化用パラメータ。
 */
CWinBase::CWinBase( const StInitParam& _rstInitParam )
	: m_stInitParam()
	, m_cClassName()
	, m_cWindowName()
	, m_hWnd( NULL )
{
	MemCopy( &m_stInitParam, &_rstInitParam, sizeof( m_stInitParam ) );
	m_cClassName = _rstInitParam.m_psClassName;
	m_cWindowName = _rstInitParam.m_psWindowName;

	// 呼び出し元で解放されて使用出来なくなる可能性があるため、ポインタはnullにしておく。
	m_stInitParam.m_psClassName = nullptr;
	m_stInitParam.m_psWindowName = nullptr;
}

/**
 * @brief	ウィンドウの作成。
 */
bool CWinBase::InitWindow()
{
	// ウィンドウクラスの登録データの設定
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = m_stInitParam.m_uClassStyle;
	wc.lpfnWndProc = WndProcWrapper;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_stInitParam.m_hInstance;
	wc.hIcon = m_stInitParam.m_hIcon;
	wc.hIconSm = m_stInitParam.m_hIconSm;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName =	m_cClassName.c_str();

	// ウィンドウクラスへの登録処理
	ATOM uAtom = RegisterClassEx( &wc );

	bool bRet = false;
	if (uAtom)
	{
		// 指定されたクライアント領域をを持つウィンドウ領域の算出
		RECT stRect = { 0, 0, m_stInitParam.m_sWidth, m_stInitParam.m_sHeight };
		AdjustWindowRect( &stRect, m_stInitParam.m_uWindowStyle, FALSE );
	
		const S32 sWindowWidth = stRect.right - stRect.left;
		const S32 sWindowHeight = stRect.bottom - stRect.top;

		m_hWnd = CreateWindow( m_cClassName.c_str(), m_cWindowName.c_str(), m_stInitParam.m_uWindowStyle,
			m_stInitParam.m_sPosX, m_stInitParam.m_sPosY, sWindowWidth, sWindowHeight, NULL, NULL, m_stInitParam.m_hInstance, this );

		if (m_hWnd)
		{
			bRet = true;
			ShowWindow( m_hWnd, m_stInitParam.m_sCmdShow );
			UpdateWindow( m_hWnd );
		}
	}

	return bRet;
}

/**
 * @brief		ウィンドウプロシージャ。
 * @param[in]	_hWnd		: ウィンドウハンドル。
 * @param[in]	_uMsg		: メッセージ。
 * @param[in]	_uWParam	: パラメータ。
 * @param[in]	_uLParam	: パラメータ。
 * @retval		LRESULT		: 処理結果。
 */
LRESULT CALLBACK CWinBase::WndProcWrapper( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam )
{
	CWinBase* pcThis = r_cast<CWinBase*>( GetWindowLongPtr( _hWnd, GWLP_USERDATA ) );

	if (WM_NCCREATE == _uMsg)
	{
		LPCREATESTRUCT pstCreateParam = r_cast<LPCREATESTRUCT>( _uLParam );
		pcThis = r_cast<CWinBase*>( pstCreateParam->lpCreateParams );
		SetWindowLongPtr( _hWnd, GWLP_USERDATA, r_cast<LONG>( pcThis ) );
	}
	
	LRESULT uRet = 0;
	if (pcThis)
	{
		uRet = pcThis->WndProc( _hWnd, _uMsg, _uWParam, _uLParam );
	}
	else
	{
		uRet = DefWindowProc( _hWnd, _uMsg, _uWParam, _uLParam );
	}

	return uRet;
}

LRESULT CWinBase::WndProc( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam )
{
	LRESULT uRet = 0;
	switch (_uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		uRet = 0;
		break;

	default:
		uRet = DefWindowProc( _hWnd, _uMsg, _uWParam, _uLParam );
		break;
	}

	return uRet;
}