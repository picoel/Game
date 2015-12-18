/**
  * @file	ConstantBufferDataForFrame.h
  * @brief	レベル用のコンスタントバッファー。
  * @date 2015/09/23 17:06:06
  */

#ifndef INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_FRAME_H
#define INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_FRAME_H

#include "Lib/Render/ConstantBufferData.h"
#include "Lib/Math/Matrix.h"

/*
 * @class CConstantBufferDataForFrame
 * @brief オブジェクト用のコンスタントバッファー。
 */
class CConstantBufferDataForFrame : public IConstantBufferData
{
public:
	/// コンスタントバッファー構造体。
	struct StConstantBufferData
	{
		StMatrix<F32>	m_stMtxDummy;

		void Init()
		{
			m_stMtxDummy.Init();
		}
	};

public:
	/// コンストラクタ。
	CConstantBufferDataForFrame();
	/// デストラクタ。
	virtual ~CConstantBufferDataForFrame(){}

	/// データを取得。
	virtual const void* GetData() const override{ return &m_stBuffer; }
	/// データサイズを取得。
	virtual USize GetSize() const override{ return sizeof( m_stBuffer ); }

private:
	StConstantBufferData m_stBuffer;
};

#endif // #ifndef INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_FRAME_H
