#ifndef INCLUDE_LIB_UTILITY_SINGLETON_H
#define INCLUDE_LIB_UTILITY_SINGLETON_H
#include "Lib/Debug/Assert.h"
#include "Lib/Memory/MemDefinition.h"

/*
 * @class	CSingleton
 * @brief	�h���N���X�ɃV���O���g���p�^�[����K�p����B
 * @note	�h���N���X��CSingleton�N���X��friend�N���X�ɂ��邱�ƁB
 */
template< class T >
class CSingleton
{
public:
	static inline void CreateInstance()
	{
		ASSERT( nullptr == sc_pcInstance );
		if (nullptr == sc_pcInstance)
		{
			sc_pcInstance = pnew T();
		}
	}

	static inline T* GetInstance()
	{
		return sc_pcInstance;
	}

	static inline void DestroyInstance()
	{
		P_DELETE( sc_pcInstance );
	}

protected:
	/// �R���X�g���N�^�B
	CSingleton(){}
	/// �f�X�g���N�^�B
	virtual	~CSingleton(){}

private:
	/// �O������̌Ăяo�����֎~����B
	/// �R�s�[�R���X�g���N�^�B
	CSingleton( const CSingleton& _rcRef ){}
	/// ������Z�q�B
	CSingleton& operator=( const CSingleton& _rcRef ){ return _rcRef; }

protected:
	static	T*	sc_pcInstance;
};

template< class T >
T* CSingleton<T>::sc_pcInstance = nullptr;

#endif // #ifndef INCLUDE_LIB_UTILITY_SINGLETON_H

