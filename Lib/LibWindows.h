/**
  * @file	LibWindows.h
  * @brief	Windows�p���C�u�����w�b�_�B
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

// �v���b�g�t�H�[���Ɉˑ�����֐����̒u�������B
#define MemCopy( DEST, SRC, SIZE ) CopyMemory( (DEST), (SRC), (SIZE) )
#define MemClear( DEST, SIZE ) ZeroMemory( (DEST), (SIZE) )

#endif // #if defiend( _WIN32 ) || defined( _WIN64 )
#endif // #ifndef INCLUDE_LIB_WINDOWS_H
