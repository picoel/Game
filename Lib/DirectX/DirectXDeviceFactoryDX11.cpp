/**
  * @file	DirectXDeviceFactoryDX11.cpp
  * @brief	DirectX11用デバイス生成クラス。
  * @date	2015/07/19 17:33:08
  */

#include "Lib/LibPrecompile.h"

#if defined( USE_DIRECTX_11 )

#include "DirectXDeviceFactoryDX11.h"

/**
 * @brief	デバイスを作成。
 * @retval	ID3DDevice*	: DirectX11デバイス。
 */
ID3DDevice* CDirectXDeviceFactoryDX11::CreateDevice()
{
	const D3D_FEATURE_LEVEL hFeatureLevelArray[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2, 
		D3D_FEATURE_LEVEL_9_1
	};

	DWORD uCreateDeviceFlag = 0;

#if defined( _DEBUG )
	uCreateDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // #if defined( _DEBUG )

	ID3DDevice* pcDevice = nullptr;
	const HRESULT hResult = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		uCreateDeviceFlag,
		hFeatureLevelArray,
		lengthof( hFeatureLevelArray ),
		D3D11_SDK_VERSION,
		&pcDevice,
		nullptr,
		nullptr
		);

	if (FAILED( hResult ))
	{
		ASSERT( !"Failed CreateDevice." );
		pcDevice = nullptr;	// failsafe
	}

	return pcDevice;
}

#endif // #if defined( USE_DIRECTX_11 )
