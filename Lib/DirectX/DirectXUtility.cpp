/**
  * @file	DirectXUtility.cpp
  * @brief	DirectX関連ユーティリティ。
  * @data 2015/12/03 03:51:33
  */
#include "Lib/LibPrecompile.h"
#include "Lib/DirectX/DirectXUtility.h"

/// ファイル名からテクスチャフォーマットを求める。
nLib::nDirectX::EnTextureFormat nLib::nDirectX::GetFormatFromFileName( const TChar* _psFileName )
{
	ASSERT( _psFileName );
	if (nullptr == _psFileName)
	{
		return EnTextureFormat::enUnknown;	// failsafe
	}

	TChar sFullPath[ MAX_PATH + 1 ];
	_fullpath( sFullPath, _psFileName, lengthof( sFullPath ) );

	TChar sExt[ MAX_PATH + 1 ];
	_splitpath( sFullPath, nullptr, nullptr, nullptr, sExt );

	EnTextureFormat eRet = EnTextureFormat::enUnknown;
	if (strcmp( sExt, ".dds" ) == 0)
	{
		eRet = EnTextureFormat::enDDS;
	}
	else if (strcmp( sExt, ".tga" ) == 0)
	{
		eRet = EnTextureFormat::enTGA;
	}
	else
	{
		eRet = EnTextureFormat::enWIC;
	}

	return eRet;
}