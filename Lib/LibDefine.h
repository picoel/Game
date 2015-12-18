/**
  * @file	LibDefine.h
  * @brief	ライブラリで使用する定義。
  * @date 2015/04/19 20:13:10
  */

#ifndef INCLUDE_LIB_H
#define INCLUDE_LIB_H

#define USE_MEMALLOC
#if defined( _DEBUG )
#	define USE_MEMORY_DEBUG			///< メモリデバッグ機能を使用する。
#	define USE_MEMORY_FAILSAFE		///< メモリアロケータでfailsafeを有効にする。
#endif // #if defined( _DEBUG )

#define USE_DIRECTX_11				///< DirectX11を使用する。

#endif // #ifndef INCLUDE_LIB_H
