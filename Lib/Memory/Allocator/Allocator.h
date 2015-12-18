/**
  * @file	Allocator.h
  * @brief	MemManager��p�����A���P�[�^�B
  * @date 2015/05/02 00:42:14
  */

#ifndef INCLUDE_ALLOCATOR_H
#define INCLUDE_ALLOCATOR_H

#include <memory>
#include "Lib/Memory/MemDefinition.h"

/*
 * @class	CAllocator
 * @brief	MemManager��p�����A���P�[�^�B
 */
template<class T>
class CAllocator : public std::allocator<T>
{
public:
	template < class U >
	struct rebind
	{
		typedef CAllocator<U> other;
	};

public:
	/// �R���X�g���N�^�B
	CAllocator(){}
	template<class U>
	CAllocator( const CAllocator<U>& _rAllocator )
	{
		UNUSED( _rAllocator );
	}

	/// �f�X�g���N�^�B
	~CAllocator(){}

	/// �������̊m�ہB
	pointer	allocate( size_type _uNum, const_pointer _hint = 0 )
	{
#if defined( USE_MEMALLOC )
		return s_cast<pointer>( nMem::Alloc( s_cast<USize>( sizeof( T ) * _uNum ), nMem::EnMemPage::enCommon, nMem::EnAllocMode::enForward, __FILE__, __LINE__ ) );
#else // #if defined( USE_MEMALLOC )
		return s_cast<pointer>( malloc( sizeof( T ) * _uNum ) );
#endif // #else // #if defined( USE_MEMALLOC )
	}
	/// �������̉���B
	void deallocate( pointer _p, size_type _uNum )
	{
#if defined( USE_MEMALLOC )
		nMem::Free( _p );
#else // #if defined( USE_MEMALLOC )
		free( _p );
#endif // #else // #if defined( USE_MEMALLOC )
	}
};

#endif // #ifndef INCLUDE_ALLOCATOR_H
