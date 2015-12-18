/**
  * @file	MemManager.h
  * @brief	�������Ǘ��N���X�B
  * @date 2015/04/19 19:39:32
  */

#ifndef INCLUDE_MEMMANAGER_H
#define INCLUDE_MEMMANAGER_H

#include "Lib/Memory/MemAllocator.h"

/*
 * @class CMemManager
 * @brief �������Ǘ��N���X�B
 */
class CMemManager
{
	// SINGLETONIZE�͂��̃N���X�̏���������������܂Ŏg�p�o���Ȃ����߁A���O�Ŏ����B
	// SINGLETONIZE( CMemManager );
public:
	static CMemManager* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();
private:
	static CMemManager* s_pInstance;
	CMemManager();

public:
	/// �f�X�g���N�^�B
	~CMemManager();

	/// �������B
	void Initialize( USize _uSize );
	/// �I�������B
	void Finalize();

	/// �������f�o�b�O���̕\���B
	void PrintDebugMemoryInfo() const;

	/// �������u���b�N����\���B
	void PrintDebugMemoryBlock( bool _bPrintUsed, bool _bPrintFree);

	/// �������m�ہB
	inline void* Alloc( USize _uSize, nMem::EnMemPage _ePage )
	{
		return m_pMemAllocator->Alloc( _uSize, NULL, 0 );
	}
	inline void* Alloc( USize _uSize, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode, const S8* _psFile, U32 _uLine )
	{
		void* pRet = nullptr;
		switch (_eMode)
		{
		case nMem::EnAllocMode::enForward:
			pRet = m_pMemAllocator->Alloc( _uSize, _psFile, _uLine );
			break;

		case nMem::EnAllocMode::enBack:
			pRet = m_pMemAllocator->AllocBack( _uSize, _psFile, _uLine );
			break;

		default:
			break;
		}
		return pRet;
	}
	/// ����������B
	inline void Free( void* _p )
	{
		if (m_pMemAllocator->IsAllocatedPointer( _p ))
		{
			m_pMemAllocator->Free( _p );
		}
		else
		{
			free( _p );
		}
	}

	static void* operator new( std::size_t _uSize )
	{
		return malloc( _uSize );
	}

	static void operator delete( void* _p )
	{
		free( _p );
	}

private:
	CMemAllocator* m_pMemAllocator;
};



#endif // #ifndef INCLUDE_MEMMANAGER_H
