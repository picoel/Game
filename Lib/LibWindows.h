/**
  * @file	LibWindows.h
  * @brief	Windows用ライブラリヘッダ。
  * @date 2015/05/15 02:54:58
  */

#ifndef INCLUDE_LIB_WINDOWS_H
#define INCLUDE_LIB_WINDOWS_H

#if defined( _WIN32 ) || defined( _WIN64 )

#include <Windows.h>
#include <tchar.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

// プラットフォームに依存する関数名の置き換え。
#define MemCopy( DEST, SRC, SIZE ) CopyMemory( (DEST), (SRC), (SIZE) )
#define MemClear( DEST, SIZE ) ZeroMemory( (DEST), (SIZE) )

#endif // #if defiend( _WIN32 ) || defined( _WIN64 )
#endif // #ifndef INCLUDE_LIB_WINDOWS_H
