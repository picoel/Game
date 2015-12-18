/**
  * @file	WinBase.h
  * @brief	�E�B���h�E�x�[�X�N���X�B
  * @date 2015/04/24 00:10:34
  */

#ifndef INCLUDE_WINBASE_H
#define INCLUDE_WINBASE_H

/*
 * @class	CWinBase
 * @brief	�E�B���h�E�̃x�[�X�N���X�B
 */
class CWinBase
{
public:
	/// �������p�p�����[�^�B
	struct StInitParam
	{
		HINSTANCE	m_hInstance;		///< �A�v���P�[�V�����n���h���B
		S32			m_sCmdShow;			///< �\�����@�B
		U32			m_uClassStyle;		///< �E�B���h�E�N���X�X�^�C���B
		U32			m_uWindowStyle;		///< �E�B���h�E�X�^�C���B
		HICON		m_hIcon;			///< �A�C�R���n���h���B
		HICON		m_hIconSm;			///< �A�C�R���n���h��(��)�B
		S32			m_sPosX;			///< �����ʒu(X)�B
		S32			m_sPosY;			///< �����ʒu(Y)�B
		S32			m_sWidth;			///< �E�B���h�E�̕��B
		S32			m_sHeight;			///< �E�B���h�E�̍����B
		LPCTSTR		m_psClassName;		///< �N���X���B
		LPCTSTR		m_psWindowName;		///< �E�B���h�E���B

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
	/// �R���X�g���N�^�B
	CWinBase( const StInitParam& _rstInitParam );
	/// �f�X�g���N�^�B
	virtual ~CWinBase(){}

	/// �E�B���h�E�̏������B
	bool InitWindow();

	/// �E�B���h�E�v���V�[�W���B
	static LRESULT CALLBACK WndProcWrapper( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam );
	virtual LRESULT WndProc( HWND _hWnd, UINT _uMsg, WPARAM _uWParam, LPARAM _uLParam );

	/// �E�B���h�E�̕����擾�B
	S32 GetWidth() const{ return m_stInitParam.m_sWidth; }
	/// �E�B���h�E�̍������擾�B
	S32 GetHeight() const{ return m_stInitParam.m_sHeight; }

	/// �E�B���h�E�n���h�����擾�B
	HWND GetWindowHandle() const{ return m_hWnd; }

protected:
	StInitParam	m_stInitParam;	///< �������p�p�����[�^�B
	CTString	m_cClassName;	///< �N���X���B
	CTString		m_cWindowName;	///< �E�B���h�E���B

	HWND		m_hWnd;
};

#endif // #ifndef INCLUDE_WINBASE_H 