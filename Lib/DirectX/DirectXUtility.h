/**
  * @file	DirectXUtility.h
  * @brief	DirectX関連ユーティリティ。
  * @data 2015/12/03 03:51:33
  */

#ifndef INCLUDE_LIB_DIRECTX_UTILITY_H
#define INCLUDE_LIB_DIRECTX_UTILITY_H

namespace nLib
{
	namespace nDirectX
	{
		/// ファイル名からテクスチャフォーマットを求める。
		EnTextureFormat GetFormatFromFileName( const TChar* _psFileName );
	};
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_UTILITY_H