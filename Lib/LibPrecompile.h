/**
  * @file	LibPrecompile.h
  * @brief	���C�u�����p�v���R���p�C���w�b�_�[
  * @date 2015/05/15 02:40:35
  */

#include <future>
#include <new>
#include <random>
#include <thread>

#include "SDK/DirectXTex/DirectXTex/DirectXTex.h"
#include "SDK/meshio/src/meshio.h"

// �v���b�g�t�H�[�����Ƃ̃C���N���[�h�B
#if defined( _WIN32 ) || defined( _WIN64 )
#include "Lib/LibWindows.h"
#endif // #if defined( _WIN32 ) || defined( _WIN64 )

#include "Lib/LibDefine.h"
#include "Lib/Type/Type.h"
#include "Lib/Utility/LibUtility.h"
#include "Lib/Utility/List.h"
#include "Lib/Utility/Range.h"
#include "Lib/Utility/Singleton.h"

#include "Lib/Debug/Assert.h"
#include "Lib/Debug/Log.h"
#include "Lib/Debug/FPSCounter.h"
#include "Lib/Debug/DebugProcessTime.h"

#include "Lib/DirectX/DirectXDefinition.h"
#include "Lib/Render/ShaderDefinition.h"
