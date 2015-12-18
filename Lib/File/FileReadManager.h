/**
  * @file	FileReadManager.h
  * @brief	ファイル読み込み管理クラス。
  * @date	2015/06/29 03:44:13
  */

#ifndef INCLUDE_LIB_FILE_FILEREADMANAGER_H
#define INCLUDE_LIB_FILE_FILEREADMANAGER_H

#include "Lib/Object/Action.h"
#include "Lib/Utility/list.h"
#include "Lib/Utility/Singleton.h"

class CFileReader;
class CFileReadThread;
class CJobFileRead;

/*
 * @class CFileReadManager
 * @brief ファイル読み込み管理クラス。
 */
class CFileReadManager 
	: public CSingleton<CFileReadManager>
	, public CAction
{
	friend CSingleton <CFileReadManager>;

public:
	/// 初期化用パラメータ。
	struct StInitParam
	{
		U32		m_uActionLv;	///< アクションレベル。
		
		void Init()
		{
			m_uActionLv = 0;
		}
	};

private:
	/// コンストラクタ。
	CFileReadManager();
	CFileReadManager( const StInitParam& _rstParam );

public:
	/// デストラクタ。
	virtual ~CFileReadManager();

	/// インスタンス作成。
	inline static void CreateInstance( const StInitParam& _rstParam )
	{
		ASSERT( nullptr == sc_pcInstance );
		P_DELETE( sc_pcInstance );
		sc_pcInstance = pnew CFileReadManager( _rstParam );
	}

	/// ファイル読み込みリクエスト。
	void Request( CFileReader* _pcFileReader );

	/// アクション処理。
	virtual void Action() override;

private:
	CVector<CJobFileRead*>	m_cJobList;
};

#endif // #ifndef INCLUDE_LIB_FILE_FILEREADMANAGER_H
