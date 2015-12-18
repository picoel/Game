/**
  * @file	DirectXDeviceFactoryDX11.h
  * @brief	DirectX11�p�f�o�C�X�����N���X�B
  * @date	2015/07/19 17:33:08
  */

#ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_DX11_H
#define INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_DX11_H

#if defined( USE_DIRECTX_11 )

#include "Lib/DirectX/DirectXDeviceFactory.h"

/*
 * @class CDirectXDeviceFactoryDX11
 * @brief DirectX11�p�f�o�C�X�����N���X�B
 */
class CDirectXDeviceFactoryDX11 : public IDirectXDeviceFactory
{
public:
	/// �R���X�g���N�^�B
	CDirectXDeviceFactoryDX11(){}
	/// �f�X�g���N�^�B
	virtual ~CDirectXDeviceFactoryDX11(){}

	/// �f�o�C�X���쐬�B
	ID3DDevice* CreateDevice();
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_DX11_H

#endif // #if defined( USE_DIRECTX_11 )
