/**
 * @file	CActionList.h
 * @brief	CAction�N���X�̃��X�g�B
 * @date	2014/12/26 09:40:53
 */

#ifndef INCLUDE_CACTIONLIST_H
#define INCLUDE_CACTIONLIST_H

class CAction;

#include "Lib/Thread/CriticalSection.h"
#include "Lib/Utility/Singleton.h"
#include "Lib/Object/ObjectList.h"

/**
 * @class	CActionList
 * @brief	CAction�N���X�̃��X�g�B
 */
class CActionList : public CSingleton<CActionList>
{
	friend CSingleton < CActionList > ;
private:
	/// �R���X�g���N�^�B
	CActionList();

public:
	/// �������p�\���́B
	struct StInitParam
	{
		U32 m_uLevelMax;			///< ���x���̍ő吔�B
		U32 m_uLevelReserveSize;	///< ���x�����̗\��T�C�Y�B

		void Init()
		{
			m_uLevelMax = 0;
			m_uLevelReserveSize = 0;
		}
	};

public:
	/// �f�X�g���N�^�B
	virtual ~CActionList();

	/// �������B
	void Init( const StInitParam& _rstParam );

	/// �o�^�����B
	void Register( CAction* _pObject );
	/// ���������B
	void UnRegister( CAction* _pObject );

	/// �A�N�V���������s�B
	void ExecAction( U32 _uActionLv );

	/// ���[�v�I�����ɍs�����������B
	void LoopEndAct();

	/// �ő僌�x�����擾�B
	U32 GetMaxLv() const{ return m_stParam.m_uLevelMax; }

private:
	StInitParam			m_stParam;

	CObjectList<CAction>*	m_pcActionList;
};

#endif // #ifndef INCLUDE_CACTIONLIST_H
