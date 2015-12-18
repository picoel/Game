/**
  * @file	PMDReader.h
  * @brief	PMDファイル読み込み。
  * @data 2015/12/02 10:41:52
  */

#ifndef INCLUDE_LIB_PMD_PMDREADER_H
#define INCLUDE_LIB_PMD_PMDREADER_H

#include "Lib/File/FileReader.h"

/*
 * @class CPMDReader
 * @brief PMDファイル読み込み。
 */
class CPMDReader : public CFileReader
{
public:
	/// コンストラクタ。
	CPMDReader( const TChar* _psFileName );
	/// デストラクタ。
	virtual ~CPMDReader();

	/// 読み込み完了時の処理。
	virtual void ReadEndProcess( const void* _pData, USize _uSize ) override;

	/// PMDデータの取得。
	const meshio::pmd::IO& GetPMDData() const{ return m_stData; }

private:
	meshio::pmd::IO	m_stData;
};

#endif // #ifndef INCLUDE_LIB_PMD_PMDREADER_H