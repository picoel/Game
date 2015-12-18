/**
 * @file	main.cpp
 * @brief	�G���g���[�|�C���g�B
 * @date	2015/02/08 22:39:43
 */
#include "PreCompileHeader.h"
#include "Windows/WinDirectX11.h"
#include "Sequence/GameSequenceFactory.h"

/**
 * @brief	�G���g���[�|�C���g�B
 */
int WINAPI _tWinMain( HINSTANCE _hCurInst, HINSTANCE _hPrevInst, LPTSTR _lpCmdLine, int _nCmdShow )
{
	//���P�[���i�n�挾��j����{��ŃZ�b�g�B
	setlocale( LC_ALL, "Japanese");  

	//timeGetTime�֐��̐��x��������B
	timeBeginPeriod(1);

	// �������A���P�[�^��L�����B
	nLib::InitMemAllocator( 512 * 1024 * 1024 );

	{
		// �E�B���h�E�̍쐬�B
		CWinBase::StInitParam stInit;
		stInit.Init();
		stInit.m_hInstance = _hCurInst;
		stInit.m_sCmdShow = _nCmdShow;
		stInit.m_sWidth = 1280;
		stInit.m_sHeight = 720;
		stInit.m_psClassName = _T( "Game" );
		stInit.m_psWindowName = _T( "Game" );
		CWinDirectX11 cWinDirectX( stInit );
		cWinDirectX.InitWindow();

		// ���C�u�����̏������B
		nLib::StLibSetting stSetting;
		stSetting.Init();
		stSetting.m_stWorkerParam.m_uWorkerSyncNum = 4;
		stSetting.m_stWorkerParam.m_uWorkerUnSyncNum = 3;
		stSetting.m_stActionParam.m_uLevelMax = s_cast<U32>(CActionLv::Max());
		stSetting.m_stActionParam.m_uLevelReserveSize = 1024;
		stSetting.m_stDrawParam.m_uLevelMax = CDrawLv::Max();
		stSetting.m_stDrawParam.m_uLevelReserveSize = 1024;
		stSetting.m_stFileReadParam.m_uActionLv = s_cast<U32>(CActionLv::System());
		stSetting.m_stSequenceParam.m_pcFactory = pnew CGameSequenceFactory();
		stSetting.m_stSequenceParam.m_uStartSequenceID = s_cast<U32>(EnSequenceID::enInit);
	
	#if defined( USE_DIRECTX_11 )
		stSetting.m_stRenderContextParam.m_hWnd = cWinDirectX.GetWindowHandle();
		stSetting.m_stRenderContextParam.m_uWidth = cWinDirectX.GetWidth();
		stSetting.m_stRenderContextParam.m_uHeight = cWinDirectX.GetHeight();
	#endif // #if defined( USE_DIRECTX_11 )

		nLib::Initialize( stSetting );

		CFPSViewer cFPSViewer( cWinDirectX.GetWindowHandle(), CActionLv::System() );

		// ���b�Z�[�W���[�v�B
		MSG	stMsg;
		MemClear( &stMsg, sizeof( stMsg ) );
		while (WM_QUIT != stMsg.message)
		{
			if (PeekMessage( &stMsg, NULL, 0, 0, PM_REMOVE ))
			{
				TranslateMessage( &stMsg );
				DispatchMessage( &stMsg );
			}

			// ���C�u��������I�����N�G�X�g�������甲����B
			if (nLib::IsEndRequest())
			{
				break;
			}
		}
	}

	// ���C�u�����̉���B
	nLib::Finalize();

	//timeGetTime�֐��̐��x��߂��B
	timeEndPeriod( 1 );
	return 0;
}
