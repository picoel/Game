/**
  * @file	DirectXDeviceFactory.h
  * @brief	DirectXDevice�����C���^�[�t�F�[�X�B
  * @date	2015/07/10 07:44:57
  */

#ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_H
#define INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_H

#include "Lib/DirectX/DirectXDefinition.h"

/*
 * @class IDirectXDeviceFactory
 * @brief DirectXDevice�����C���^�[�t�F�[�X�B
 */
class IDirectXDeviceFactory
{
public:
	/// �R���X�g���N�^�B
	IDirectXDeviceFactory(){}
	/// �f�X�g���N�^�B
	virtual ~IDirectXDeviceFactory(){}

	/// �f�o�C�X���쐬�B
	virtual ID3DDevice* CreateDevice() = 0;
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_DEVICE_FACTORY_H
