/**
  * @file	WinBase.h
  * @brief	�E�B���h�E�x�[�X�N���X�B
  * @date 2015/05/02 02:47:45
  */

#include "PreCompileHeader.h"
#include "Windows\WinBase.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_rstInitParam	: �������p�p�����[�^�B
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

	// �Ăяo�����ŉ������Ďg�p�o���Ȃ��Ȃ�\�������邽�߁A�|�C���^��null�ɂ��Ă����B
	m_stInitParam.m_psClassName = nullptr;
	m_stInitParam.m_psWindowName = nullptr;
}

/**
 * @brief	�E�B���h�E�̍쐬�B
 */
bool CWinBase::InitWindow()
{
	// �E�B���h�E�N���X�̓o�^�f�[�^�̐ݒ�
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

	// �E�B���h�E�N���X�ւ̓o�^����
	ATOM uAtom = RegisterClassEx( &wc );

	bool bRet = false;
	if (uAtom)
	{
		// �w�肳�ꂽ�N���C�A���g�̈�������E�B���h�E�̈�̎Z�o
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
 * @brief		�E�B���h�E�v���V�[�W���B
 * @param[in]	_hWnd		: �E�B���h�E�n���h���B
 * @param[in]	_uMsg		: ���b�Z�[�W�B
 * @param[in]	_uWParam	: �p�����[�^�B
 * @param[in]	_uLParam	: �p�����[�^�B
 * @retval		LRESULT		: �������ʁB
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