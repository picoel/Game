/**
  * @file	DirectXShaderManager.cpp
  * @brief	シェーダー管理クラス。
  * @date 2015/09/13 04:16:50
  */

#include "Lib/LibPrecompile.h"

#include "Lib/DirectX/DirectXShaderManager.h"
#include "Lib/DirectX/VertexShader.h"
#include "Lib/DirectX/PixelShader.h"

/**
 * @brief	コンストラクタ。
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
 * @brief	デストラクタ。
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
 * @brief		頂点シェーダーを取得。
 * @param[in]	_eVertexShader			: 取得する頂点シェーダー。
 * @retval		const CVertexShader*	: 頂点シェーダー。
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
 * @brief		ピクセルシェーダーを取得。
 * @param[in]	_ePixelShader		: 取得するピクセルシェーダー。
 * @retval		const CPixelShader*	: ピクセルシェーダー。
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
 * @brief	読み込みが完了したか。
 * @retval	bool	: 全てのシェーダーが使用可能になればtrue。
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