#ifndef INCLUDE_LIB_UTILITY_SINGLETON_H
#define INCLUDE_LIB_UTILITY_SINGLETON_H
#include "Lib/Debug/Assert.h"
#include "Lib/Memory/MemDefinition.h"

/*
 * @class	CSingleton
 * @brief	派生クラスにシングルトンパターンを適用する。
 * @note	派生クラスでCSingletonクラスをfriendクラスにすること。
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
	/// コンストラクタ。
	CSingleton(){}
	/// デストラクタ。
	virtual	~CSingleton(){}

private:
	/// 外部からの呼び出しを禁止する。
	/// コピーコンストラクタ。
	CSingleton( const CSingleton& _rcRef ){}
	/// 代入演算子。
	CSingleton& operator=( const CSingleton& _rcRef ){ return _rcRef; }

protected:
	static	T*	sc_pcInstance;
};

template< class T >
T* CSingleton<T>::sc_pcInstance = nullptr;

#endif // #ifndef INCLUDE_LIB_UTILITY_SINGLETON_H

