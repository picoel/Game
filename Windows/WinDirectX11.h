/**
  * @file	WinDirectX11.h
  * @brief	DirectX11���g�p�����E�B���h�E�N���X�B
  * @date 2015/05/03 19:12:24
  */

#ifndef INCLUDE_WINDIRECTX11_H
#define INCLUDE_WINDIRECTX11_H

#include "Windows/WinBase.h"

/*
 * @class	CWinDirectX11
 * @brief	DirectX11���g�p�����E�B���h�E�N���X�B
 */
class CWinDirectX11 
	: public CWinBase
{
public:
	/// �R���X�g���N�^�B
	CWinDirectX11( const StInitParam& _rstInitParam );
	/// �f�X�g���N�^�B
	virtual ~CWinDirectX11();

	/// �E�B���h�E�v���V�[�W���B
	virtual LRESULT WndProc( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam ) final;
};

#endif // #ifndef INCLUDE_WINDIRECTX11_H
