/**
  * @file	DirectX.cpp
  * @brief	DirectX�֘A�̊Ǘ��B
  * @date	2015/07/19 17:51:51
  */

#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/DirectX.h"
#include "Lib/DirectX/DirectXDeviceFactory.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CDirectX::CDirectX()
	: CSingleton< CDirectX >()
	, m_pcDevice( nullptr )
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CDirectX::~CDirectX()
{
	SAFE_RELEASE( m_pcDevice );
}

/**
 * @brief		�������B
 * @param[in]	_pcFactory	: �f�o�C�X�����N���X�B
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
 * @brief		�f�o�C�X���擾�B
 * @retval		ID3DDevice*	: DirectXDevice�B
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
