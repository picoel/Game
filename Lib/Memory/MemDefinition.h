/**
  * @file	MemDefinition.h
  * @brief	メモリ関連の定義。
  * @date 2015/05/24 03:54:05
  */

#ifndef INCLUDE_LIB_MEMORY_MEM_DEGINITION_H
#define INCLUDE_LIB_MEMORY_MEM_DEGINITION_H

namespace nMem
{
	enum class EnMemPage : U32
	{
		enStationed,	///< 常駐メモリページ。
		enCommon,		///< コモンページ。

		enMax,
	};

	enum class EnAllocMode : U32
	{
		enForward,
		enBack,
	};

	/// メモリ確保。
	void* Alloc( USize _uSize, EnMemPage _ePage, EnAllocMode _eMode, const S8* _psFile, U32 _uLine );
	/// メモリ解放。
	void Free( void* _p );
}

// new演算子のオーバーライド。
inline void* operator new( std::size_t _uSize, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode, const S8* _psFile, U32 _uLine ) throw()
{
	return nMem::Alloc( s_cast<USize>(_uSize), _ePage, _eMode, _psFile, _uLine );
}

inline void* operator new[]( std::size_t _uSize, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode, const S8* _psFile, U32 _uLine ) throw()
{
	return ::operator new( _uSize, _ePage, _eMode, _psFile, _uLine );
}

inline void* operator new( std::size_t _uSize, nMem::EnMemPage _ePage , nMem::EnAllocMode _eMode ) throw()
{
	return nMem::Alloc( s_cast<USize>(_uSize), _ePage, _eMode, nullptr, 0 );
}

inline void* operator new[]( std::size_t _uSize, nMem::EnMemPage _ePage , nMem::EnAllocMode _eMode ) throw()
{
	return ::operator new( _uSize, _ePage, _eMode );
}

// delete演算子のオーバーライド。
#if defined( USE_MEMALLOC )
inline void operator delete( void* _p ) throw()
{
	nMem::Free( _p );
}

inline void operator delete[]( void* _p ) throw()
{
	::operator delete( _p );
}

inline void operator delete( void* _p, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode, const S8* _psFile, U32 _uLine ) throw()
{
	UNUSED( _ePage );
	UNUSED( _eMode );
	UNUSED( _psFile );
	UNUSED( _uLine );
	::operator delete( _p );
}

inline void operator delete[]( void* _p, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode, const S8* _psFile, U32 _uLine ) throw()
{
	UNUSED( _ePage );
	UNUSED( _eMode );
	UNUSED( _psFile );
	UNUSED( _uLine );
	::operator delete( _p );
}

inline void operator delete( void* _p, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode ) throw()
{
	UNUSED( _ePage );
	UNUSED( _eMode );
	::operator delete( _p );
}

inline void operator delete[]( void* _p, nMem::EnMemPage _ePage, nMem::EnAllocMode _eMode ) throw()
{
	::operator delete( _p, _ePage, _eMode );
}
#endif // #if defined( USE_MEMALLOC )

// newキーワードのマクロ置き換え。
#if defined( USE_MEMALLOC )
#if defined( _DEBUG )
#	define pnew new( nMem::EnMemPage::enCommon, nMem::EnAllocMode::enForward, __FILE__, __LINE__)
#	define ptempnew new( nMem::EnMemPage::enCommon, nMem::EnAllocMode::enBack, __FILE__, __LINE__)
#else
#	define pnew new( nMem::EnMemPage::enCommon, nMem::EnAllocMode::enForward )
#	define ptempnew new( nMem::EnMemPage::enCommon, nMem::EnAllocMode::enBack )
#endif
#else // #if defined( USE_MEMALLOC )
#	define pnew new
#endif // #else // #if defined( USE_MEMALLOC )


// deleteキーワードのマクロ置き換え。セーフコードとnullptr代入。
#define P_DELETE(p) if(p){ delete p; p = nullptr;}
#define P_DELETE_ARRAY(p) if(p){ delete[] p; p = nullptr; }

#endif // #ifndef INCLUDE_LIB_MEMORY_MEM_DEGINITION_H