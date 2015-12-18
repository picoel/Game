/**
  * @file	DirectX.h
  * @brief	DirectX�֘A�̊Ǘ��B
  * @date	2015/07/19 17:51:51
  */

#ifndef INCLUDE_LIB_DIRECX_H
#define INCLUDE_LIB_DIRECX_H

#include "Lib/DirectX/DirectXDefinition.h"
#include "Lib/Utility/Singleton.h"

class IDirectXDeviceFactory;

/*
 * @class CDirectX
 * @brief DirectX�̊Ǘ��B
 */
class CDirectX : public CSingleton < CDirectX >
{
private:
	friend CSingleton < CDirectX > ;

	/// �R���X�g���N�^�B
	CDirectX();

public:
	/// �f�X�g���N�^�B
	virtual ~CDirectX();

	/// �������B
	void Init( IDirectXDeviceFactory* _pcFactory );

	/// �f�o�C�X���擾�B
	static ID3DDevice* GetDevice();

private:
	ID3DDevice*	m_pcDevice;
};

#endif // #ifndef INCLUDE_LIB_DIRECX_H
