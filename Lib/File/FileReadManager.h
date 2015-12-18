/**
  * @file	FileReadManager.h
  * @brief	�t�@�C���ǂݍ��݊Ǘ��N���X�B
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
 * @brief �t�@�C���ǂݍ��݊Ǘ��N���X�B
 */
class CFileReadManager 
	: public CSingleton<CFileReadManager>
	, public CAction
{
	friend CSingleton <CFileReadManager>;

public:
	/// �������p�p�����[�^�B
	struct StInitParam
	{
		U32		m_uActionLv;	///< �A�N�V�������x���B
		
		void Init()
		{
			m_uActionLv = 0;
		}
	};

private:
	/// �R���X�g���N�^�B
	CFileReadManager();
	CFileReadManager( const StInitParam& _rstParam );

public:
	/// �f�X�g���N�^�B
	virtual ~CFileReadManager();

	/// �C���X�^���X�쐬�B
	inline static void CreateInstance( const StInitParam& _rstParam )
	{
		ASSERT( nullptr == sc_pcInstance );
		P_DELETE( sc_pcInstance );
		sc_pcInstance = pnew CFileReadManager( _rstParam );
	}

	/// �t�@�C���ǂݍ��݃��N�G�X�g�B
	void Request( CFileReader* _pcFileReader );

	/// �A�N�V���������B
	virtual void Action() override;

private:
	CVector<CJobFileRead*>	m_cJobList;
};

#endif // #ifndef INCLUDE_LIB_FILE_FILEREADMANAGER_H
