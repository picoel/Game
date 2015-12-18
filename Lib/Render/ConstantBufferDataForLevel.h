/**
  * @file	ConstantBufferDataForLevel.h
  * @brief	レベル用のコンスタントバッファー。
  * @date 2015/09/23 17:06:06
  */

#ifndef INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_LEVEL_H
#define INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_LEVEL_H

#include "Lib/Render/ConstantBufferData.h"
#include "Lib/Math/Matrix.h"

/*
 * @class CConstantBufferDataForLevel
 * @brief オブジェクト用のコンスタントバッファー。
 */
class CConstantBufferDataForLevel : public IConstantBufferData
{
public:
	/// コンスタントバッファー構造体。
	struct StConstantBufferData
	{
		StMatrix<F32>	m_stMtxView;
		StMatrix<F32>	m_stMtxProjection;

		void Init()
		{
			m_stMtxView.Init();
			m_stMtxProjection.Init();
		}
	};

public:
	/// コンストラクタ。
	CConstantBufferDataForLevel();
	/// デストラクタ。
	virtual ~CConstantBufferDataForLevel(){}

	/// データを取得。
	virtual const void* GetData() const override{ return &m_stBuffer; }
	/// データサイズを取得。
	virtual USize GetSize() const override{ return sizeof( m_stBuffer ); }

private:
	StConstantBufferData m_stBuffer;
};

#endif // #ifndef INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_LEVEL_H
