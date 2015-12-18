/**
  * @file	DirectXShaderManager.cpp
  * @brief	�V�F�[�_�[�Ǘ��N���X�B
  * @date 2015/09/13 04:16:50
  */

#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/DirectXShaderManager.h"
#include "Lib/DirectX/VertexShader.h"
#include "Lib/DirectX/PixelShader.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CDirectXShaderManager::CDirectXShaderManager()
{
	for (U32 ii = 0; ii < lengthof( m_pcVertexShaderArray ); ++ii)
	{
		ASSERT( ii < lengthof( nDirectXData::sc_stVertexShaderInfoArray ) );
		if (lengthof( nDirectXData::sc_stVertexShaderInfoArray ) < ii)
		{
			break;	// failsafe
		}

		CVertexShader::StInitParam stInit;
		stInit.Init();
		stInit.m_psFileName = nDirectXData::sc_stVertexShaderInfoArray[ ii ].m_psFileName;

		m_pcVertexShaderArray[ ii ] = pnew CVertexShader( stInit );
	}

	for (U32 ii = 0; ii < lengthof( m_pcPixelShaderArray ); ++ii)
	{
		ASSERT( ii < lengthof( nDirectXData::sc_stPixelShaderInfoArray ) );
		if (lengthof( nDirectXData::sc_stPixelShaderInfoArray ) < ii)
		{
			break;	// failsafe
		}

		CPixelShader::StInitParam stInit;
		stInit.Init();
		stInit.m_psFileName = nDirectXData::sc_stPixelShaderInfoArray[ ii ].m_psFileName;

		m_pcPixelShaderArray[ ii ] = pnew CPixelShader( stInit );
	}
}

/**
 * @brief	�f�X�g���N�^�B
 */
CDirectXShaderManager::~CDirectXShaderManager()
{
	for (U32 ii = 0; ii < lengthof( m_pcVertexShaderArray ); ++ii)
	{
		P_DELETE( m_pcVertexShaderArray[ ii ] );
	}

	for (U32 ii = 0; ii < lengthof( m_pcPixelShaderArray ); ++ii)
	{
		P_DELETE( m_pcPixelShaderArray[ ii ] );
	}
}

/**
 * @brief		���_�V�F�[�_�[���擾�B
 * @param[in]	_eVertexShader			: �擾���钸�_�V�F�[�_�[�B
 * @retval		const CVertexShader*	: ���_�V�F�[�_�[�B
 */
const CVertexShader* CDirectXShaderManager::GetVertexShader( EnVertexShader _eVertexShader ) const
{
	ASSERT( s_cast<U32>(_eVertexShader) < lengthof( m_pcVertexShaderArray ) );
	if (lengthof(m_pcVertexShaderArray) <= s_cast<U32>(_eVertexShader))
	{
		return nullptr;	// failsafe
	}

	return m_pcVertexShaderArray[ s_cast<U32>( _eVertexShader ) ];
}

/**
 * @brief		�s�N�Z���V�F�[�_�[���擾�B
 * @param[in]	_ePixelShader		: �擾����s�N�Z���V�F�[�_�[�B
 * @retval		const CPixelShader*	: �s�N�Z���V�F�[�_�[�B
 */
const CPixelShader* CDirectXShaderManager::GetPixelShader( EnPixelShader _ePixelShader ) const
{
	ASSERT( s_cast<U32>(_ePixelShader) < lengthof( m_pcPixelShaderArray ) );
	if (lengthof(m_pcPixelShaderArray) <= s_cast<U32>(_ePixelShader))
	{
		return nullptr;	// failsafe
	}

	return m_pcPixelShaderArray[ s_cast<U32>( _ePixelShader ) ];
}

/**
 * @brief	�ǂݍ��݂������������B
 * @retval	bool	: �S�ẴV�F�[�_�[���g�p�\�ɂȂ��true�B
 */
bool CDirectXShaderManager::IsReadEnd() const
{
	bool bRet = true;

	for (auto* pcVertexShader : m_pcVertexShaderArray)
	{
		if (nullptr == pcVertexShader)
		{
			continue;
		}
		
		if (pcVertexShader->IsReadEnd())
		{
			continue;
		}

		bRet = false;
		break;
	}

	for (auto* pcPixelShader : m_pcPixelShaderArray)
	{
		if (nullptr == pcPixelShader)
		{
			continue;
		}
		
		if (pcPixelShader->IsReadEnd())
		{
			continue;
		}

		bRet = false;
		break;
	}

	return bRet;
}