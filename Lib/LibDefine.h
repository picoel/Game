/**
  * @file	LibDefine.h
  * @brief	���C�u�����Ŏg�p�����`�B
  * @date 2015/04/19 20:13:10
  */

#ifndef INCLUDE_LIB_H
#define INCLUDE_LIB_H

#define USE_MEMALLOC
#if defined( _DEBUG )
#	define USE_MEMORY_DEBUG			///< �������f�o�b�O�@�\���g�p����B
#	define USE_MEMORY_FAILSAFE		///< �������A���P�[�^��failsafe��L���ɂ���B
#endif // #if defined( _DEBUG )

#define USE_DIRECTX_11				///< DirectX11���g�p����B

#endif // #ifndef INCLUDE_LIB_H
