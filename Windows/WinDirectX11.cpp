/**
  * @file	WinDirectX11.cpp
  * @brief	DirectX11���g�p�����E�B���h�E�N���X�B
  * @date 2015/05/03 19:12:24
  */

#include "PreCompileHeader.h"
#include "Windows/WinDirectX11.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_rstInitParam	: �������p�p�����[�^�B
 */
CWinDirectX11::CWinDirectX11( const StInitParam& _rstInitParam )
	: CWinBase( _rstInitParam )
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CWinDirectX11::~CWinDirectX11()
{
}

/**
 * @brief		�E�B���h�E�v���V�[�W���B
 * @param[in]	_hWnd		: �E�B���h�E�n���h���B
 * @param[in]	_uMsg		: ���b�Z�[�W�B
 * @param[in]	_uWParam	: �p�����[�^�B
 * @param[in]	_uLParam	: �p�����[�^�B
 * @retval		LRESULT		: �������ʁB
 */
LRESULT CWinDirectX11::WndProc( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam )
{
	LRESULT uRet = 0;
	switch (_uMsg)
	{
	// �L�[�̉����B
	case WM_KEYDOWN:
		// ESCAPE�L�[�̉����ŃE�B���h�E�I���B
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
