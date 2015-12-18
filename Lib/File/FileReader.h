/**
  * @file	FileReader.h
  * @brief	ファイル読み込みクラス。
  * @date	2015/06/29 03:58:07
  */

#ifndef INCLUDE_LIB_FILE_FILEREADER_H
#define INCLUDE_LIB_FILE_FILEREADER_H

#include "Lib/String/String.h"

/*
 * @class	CFileReader
 * @brief	ファイル読み込みクラス。
 */
class CFileReader
{
public:
	/// コンストラクタ。
	CFileReader( const TChar* _psFileName );
	/// デストラクタ。
	virtual ~CFileReader(){}

	/// 読み込み完了時の処理。
	virtual void ReadEndProcess( const void* _pData, USize _uSize ){}
	/// 読み込み完了時の処理(メインスレッドと同期)。
	virtual void ReadEndProcessSync(){}

	/// 読み込むファイル名を取得。
	const TChar* GetFileName() const{ return m_cFileName.c_str(); }

	/// 読み込みが完了したか。
	bool IsReadEnd() const{ return m_bIsReadEnd; }
	/// 読み込みが完了したか設定。
	void SetReadEnd( bool _bEnd ){ m_bIsReadEnd = _bEnd; }

private:
	CTString	m_cFileName;
	bool		m_bIsReadEnd;
};

#endif // #ifndef INCLUDE_LIB_FILE_FILEREADER_H
