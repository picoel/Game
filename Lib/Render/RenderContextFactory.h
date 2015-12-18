/**
  * @file	RenderContextFactory.h
  * @brief	描画コンテキスト生成クラス。
  * @data 2015/11/15 19:35:04
  */

#ifndef INCLUDE_LIB_RENDER_CONTEXT_FACTORY_H
#define INCLUDE_LIB_RENDER_CONTEXT_FACTORY_H

class IRenderContext;

/*
 * @class IRenderContextFactory
 * @brief 描画コンテキスト生成クラス。
 */
class IRenderContextFactory
{
public:
	/// コンストラクタ。
	IRenderContextFactory(){}
	/// デストラクタ。
	virtual ~IRenderContextFactory(){}

	/// 生成。
	virtual IRenderContext*	Create() = 0;
};

#endif // #ifndef INCLUDE_LIB_RENDER_CONTEXT_FACTORY_H
