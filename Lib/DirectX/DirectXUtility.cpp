/**
  * @file	DirectXUtility.cpp
  * @brief	DirectX�֘A���[�e�B���e�B�B
  * @data 2015/12/03 03:51:33
  */
#include "Lib/LibPrecompile.h"
#include "Lib/DirectX/DirectXUtility.h"

/// �t�@�C��������e�N�X�`���t�H�[�}�b�g�����߂�B
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