/**
  * @file	List.h
  * @brief	動的配列定義。
  * @date 2015/05/23 04:16:10
  */
#ifndef INCLUDE_UTILITY_LIST_H
#define INCLUDE_UTILITY_LIST_H

#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <memory>
#include "Lib/Memory/Allocator/Allocator.h"

template< class C >
using CVector = std::vector < C, CAllocator<C> > ;

template< class C >
using CList = std::list < C, CAllocator<C> > ;

template< class C >
using CDeque = std::deque < C, CAllocator<C> > ;

template< class C >
using CQueue = std::queue < C, CDeque<C> >;

#endif // #ifndef INCLUDE_UTILITY_LIST_H
