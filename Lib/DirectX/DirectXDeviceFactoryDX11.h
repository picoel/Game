/**
  * @file	DirectXDeviceFactoryDX11.h
  * @brief	DirectX11用デバイス生成クラス。
  * @date	2015/07/19 17:33:08
  */

#ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_DX11_H
#define INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_DX11_H

#if defined( USE_DIRECTX_11 )

#include "Lib/DirectX/DirectXDeviceFactory.h"

/*
 * @class CDirectXDeviceFactoryDX11
 * @brief DirectX11用デバイス生成クラス。
 */
class CDirectXDeviceFactoryDX11 : public IDirectXDeviceFactory
{
public:
	/// コンストラクタ。
	CDirectXDeviceFactoryDX11(){}
	/// デストラクタ。
	virtual ~CDirectXDeviceFactoryDX11(){}

	/// デバイスを作成。
	ID3DDevice* CreateDevice();
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_DX11_H

#endif // #if defined( USE_DIRECTX_11 )
