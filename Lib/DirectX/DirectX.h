/**
  * @file	DirectX.h
  * @brief	DirectX関連の管理。
  * @date	2015/07/19 17:51:51
  */

#ifndef INCLUDE_LIB_DIRECX_H
#define INCLUDE_LIB_DIRECX_H

#include "Lib/DirectX/DirectXDefinition.h"
#include "Lib/Utility/Singleton.h"

class IDirectXDeviceFactory;

/*
 * @class CDirectX
 * @brief DirectXの管理。
 */
class CDirectX : public CSingleton < CDirectX >
{
private:
	friend CSingleton < CDirectX > ;

	/// コンストラクタ。
	CDirectX();

public:
	/// デストラクタ。
	virtual ~CDirectX();

	/// 初期化。
	void Init( IDirectXDeviceFactory* _pcFactory );

	/// デバイスを取得。
	static ID3DDevice* GetDevice();

private:
	ID3DDevice*	m_pcDevice;
};

#endif // #ifndef INCLUDE_LIB_DIRECX_H
