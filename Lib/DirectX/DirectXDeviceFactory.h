/**
  * @file	DirectXDeviceFactory.h
  * @brief	DirectXDevice生成インターフェース。
  * @date	2015/07/10 07:44:57
  */

#ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_H
#define INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_H

#include "Lib/DirectX/DirectXDefinition.h"

/*
 * @class IDirectXDeviceFactory
 * @brief DirectXDevice生成インターフェース。
 */
class IDirectXDeviceFactory
{
public:
	/// コンストラクタ。
	IDirectXDeviceFactory(){}
	/// デストラクタ。
	virtual ~IDirectXDeviceFactory(){}

	/// デバイスを作成。
	virtual ID3DDevice* CreateDevice() = 0;
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_H
