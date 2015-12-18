/**
  * @file	Lib.h
  * @brief	ライブラリを使用するためのインクルードファイル。
  * @date 2015/08/26 23:29:13
  */

#ifndef INCLUDE_LIB_LIB_H
#define INCLUDE_LIB_LIB_H

// 外部に公開するヘッダファイル。

// プラットフォームごとのインクルード。
#if defined( _WIN32 ) || defined( _WIN64 )
#include "Lib/LibWindows.h"
#endif // #if defined( _WIN32 ) || defined( _WIN64 )

#include "Lib/LibDefine.h"
#include "Lib/Type/Type.h"
#include "Lib/Utility/LibUtility.h"
#include "Lib/Utility/List.h"
#include "Lib/Utility/Range.h"
#include "Lib/Utility/Singleton.h"

#include "SDK/meshio/src/meshio.h"

#include "Lib/Debug/Assert.h"
#include "Lib/Debug/Log.h"
#include "Lib/Debug/FPSCounter.h"
#include "Lib/Debug/FPSViewer.h"
#include "Lib/Debug/DebugProcessTime.h"
#include "Lib/DirectX/DirectX.h"
#include "Lib/DirectX/DirectXDefinition.h"
#include "Lib/DirectX/DirectXDeviceFactory.h"
#include "Lib/DirectX/DirectXDeviceFactoryDX11.h"
#include "Lib/DirectX/RenderContextDX11.h"
#include "Lib/DirectX/RenderContextFactoryDX11.h"
#include "Lib/File/FileReader.h"
#include "Lib/File/FileReadManager.h"
#include "Lib/MainLoop/MainLoopThread.h"
#include "Lib/Math/Bit.h"
#include "Lib/Math/Vector.h"
#include "Lib/Math/Matrix.h"
#include "Lib/Mesh/Mesh.h"
#include "Lib/Mesh/MeshDrawer.h"
#include "Lib/Memory/MemDefinition.h"
#include "Lib/Object/ActionList.h"
#include "Lib/Object/Action.h"
#include "Lib/Object/Draw.h"
#include "Lib/Object/DrawList.h"
#include "Lib/PMD/PMDReader.h"
#include "Lib/PMD/PMDMesh.h"
#include "Lib/Render/RenderContext.h"
#include "Lib/Render/RenderThread.h"
#include "Lib/Random/Random.h"
#include "Lib/Sequence/Sequence.h"
#include "Lib/Sequence/SequenceControl.h"
#include "Lib/Sequence/SequenceFactory.h"
#include "Lib/String/String.h"
#include "Lib/Thread/CriticalSection.h"
#include "Lib/Thread/Thread.h"
#include "Lib/Worker/Job.h"
#include "Lib/Worker/Worker.h"

namespace nLib
{
	/// ライブラリの設定。
	struct StLibSetting
	{
		CWorker::StInitParam			m_stWorkerParam;
		CActionList::StInitParam		m_stActionParam;
		CDrawList::StInitParam			m_stDrawParam;
		CFileReadManager::StInitParam	m_stFileReadParam;
		CSequenceControl::StInitParam	m_stSequenceParam;
		
	#if defined( USE_DIRECTX_11 )
		CRenderContextDX11::StInitParam	m_stRenderContextParam;
	#endif // #if defined( USE_DIRECTX_11 )

		void Init()
		{
			m_stWorkerParam.Init();
			m_stActionParam.Init();
			m_stDrawParam.Init();
			m_stFileReadParam.Init();
			m_stSequenceParam.Init();

		#if defined( USE_DIRECTX_11 )
			m_stRenderContextParam.Init();
		#endif // #if defined( USE_DIRECTX_11 )
		}
	};

	/// メモリアロケータの初期化。
	void InitMemAllocator( USize _uMemSize );
	/// ライブラリの初期化処理。
	void Initialize( const StLibSetting& _rstSetting );
	/// ライブラリの終了処理。
	void Finalize();

	/// 終了リクエストがあるか。
	bool IsEndRequest();
}

#endif // #ifndef INCLUDE_LIB_LIB_H