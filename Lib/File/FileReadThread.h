/**
  * @file	FileReadThread.h
  * @brief	非同期ファイル読み込みスレッド。
  * @date	2015/06/29 05:35:57
  */

#ifndef INCLUDE_LIB_FILE_FILEREADTHREAD_H
#define INCLUDE_LIB_FILE_FILEREADTHREAD_H

#include "Lib/String/String.h"
#include "Lib/Thread/Thread.h"
#include "Lib/Thread/CriticalSection.h"

/*
 * @class CFileReadThread
 * @brief 非同期ファイル読み込みスレッド。
 */
class CFileReadThread	: public CThread
{
public:
	/// コンストラクタ。
	CFileReadThread();
	/// デストラクタ。
	virtual ~CFileReadThread();

	/// 開始したスレッドから呼ばれるコールバック関数。
	virtual void ThreadCallback() override;

	/// ファイル読み込みリクエスト。
	void Request( const TChar* _psFileName );
	/// スレッド終了リクエスト。
	void RequestEndThread()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		m_bRequestEnd = true;
	}

	/// 読み込みが終了したか。
	bool IsReadEnd()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		return m_bIsReadEnd; 
	}
	/// 読み込んだデータを取得。
	void* GetData()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		return m_pData;
	}
	/// 読み込んだデータサイズを取得。
	USize GetSize()
	{
		CCriticalSectionBlock cCSBlock( &m_cCriticalSection );
		return m_uSize;
	}

private:
	CTString				m_cFileName;
	bool					m_bIsRequest;
	bool					m_bIsReadEnd;
	bool					m_bRequestEnd;

	void*					m_pData;
	USize					m_uSize;
	CCriticalSection		m_cCriticalSection;
};

#endif // #ifndef INCLUDE_LIB_FILE_FILEREADTHREAD_H
