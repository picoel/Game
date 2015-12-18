/**
  * @file	DirectX.cpp
  * @brief	DirectX関連の管理。
  * @date	2015/07/19 17:51:51
  */

#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/DirectX.h"
#include "Lib/DirectX/DirectXDeviceFactory.h"

/**
 * @brief	コンストラクタ。
 */
CDirectX::CDirectX()
	: CSingleton< CDirectX >()
	, m_pcDevice( nullptr )
{
}

/**
 * @brief	デストラクタ。
 */
CDirectX::~CDirectX()
{
	SAFE_RELEASE( m_pcDevice );
}

/**
 * @brief		初期化。
 * @param[in]	_pcFactory	: デバイス生成クラス。
 */
void CDirectX::Init( IDirectXDeviceFactory* _pcFactory )
{
	ASSERT( _pcFactory );
	if (nullptr == _pcFactory)
	{
		return;	// failsafe
	}

	ASSERT( nullptr == m_pcDevice );
	SAFE_RELEASE( m_pcDevice );
	m_pcDevice = _pcFactory->CreateDevice();
}

/**
 * @brief		デバイスを取得。
 * @retval		ID3DDevice*	: DirectXDevice。
 */
ID3DDevice* CDirectX::GetDevice()
{
	auto* pcDirectX = GetInstance();
	ASSERT( pcDirectX );
	if (nullptr == pcDirectX)
	{
		return nullptr;	// failsafe
	}

	return pcDirectX->m_pcDevice;
}
