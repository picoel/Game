/**
  * @file	JobFileRead.h
  * @brief	ファイル読み込みジョブクラス。
  * @date	2015/08/09 00:59:20
  */

#ifndef INCLUDE_LIB_FILE_JOB_FILEREAD_H
#define INCLUDE_LIB_FILE_JOB_FILEREAD_H

#include "Lib/Worker/Job.h"

class CFileReader;

/*
 * @class CJobFileRead
 * @brief ファイル読み込みジョブ。
 */
class CJobFileRead : public CJob
{
public:
	/// コンストラクタ。
	CJobFileRead( CFileReader* _pcReader );
	/// デストラクタ。
	virtual ~CJobFileRead(){}

	/// ワーカースレッドで行う処理。
	virtual void Run() override;

	/// ファイルリーダーを取得。
	CFileReader* GetFileReader() const{ return m_pcReader; }

private:
	CFileReader*	m_pcReader;
};

#endif // #ifndef INCLUDE_LIB_FILE_JOB_FILEREAD_H