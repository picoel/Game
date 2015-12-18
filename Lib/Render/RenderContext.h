/**
  * @file	RenderContext.h
  * @brief	描画コンテキスト。
  * @date 2015/05/21 06:06:18
  */

#ifndef INCLUDE_RENDER_CONTEXT_H
#define INCLUDE_RENDER_CONTEXT_H

#include "Lib/Render/ConstantBufferData.h"

/*
 * @class IRenderContext
 * @brief 描画コンテキストインターフェース。
 */
class IRenderContext
{
public:
	/// デストラクタ。
	virtual ~IRenderContext(){}

	/// 描画。
	virtual void Render() = 0;
	/// 画面のクリア。
	virtual void Clear() = 0;

	/// ポリゴンを描画。
	virtual void DrawIndexed( U32 _uIndexNum, U32 _uOffset ) = 0;

	/// 使用可能かどうか。
	virtual bool IsEnabled() const{ return true; }

	//#TODO 描画に必要な処理を追加する。

	/// コンスタントバッファの更新。
	virtual void UpdateConstantBuffer( void* _pcBuffer, const IConstantBufferData& _rcData ) = 0;
	/// コンスタントバッファの設定。
	virtual void SetConstantBuffer( EnConstantBuffer _eKind, void* _pcConstantBuffer ) = 0;

	/// 頂点バッファの設定。
	virtual void SetVertexBuffer( U32 _uSlot, void* _pcBuffer, U32 _uStride, U32 _uOffset ) = 0;
	/// インデックスバッファの設定。
	virtual void SetIndexBuffer( void* _pcBuffer, U32 _uOffset ) = 0;
	/// プリミティブトポロジーを設定。
	virtual void SetPrimitiveTopology( U32 _uPrimitive ) = 0;

	/// テクスチャを設定。
	virtual void SetTexture( U32 _uSlot, void* _pcTexture ) = 0;

	/// 頂点シェーダーの設定。
	virtual void SetVertexShader( EnVertexShader _eShader ) = 0;
	/// ピクセルシェーダーの設定。
	virtual void SetPixelShader( EnPixelShader _eShader ) = 0;
};

#endif // #ifndef INCLUDE_RENDER_CONTEXT_H
