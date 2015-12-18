/**
  * @file	Range.h
  * @brief	範囲クラス。
  * @date 2015/06/08 01:04:32
  */
#ifndef INCLUDE_LIB_UTILITY_RANGE_H
#define INCLUDE_LIB_UTILITY_RANGE_H

#include "Lib/Utility/LibUtility.h"
#include "Lib/Debug/Assert.h"

/*
 * @class CRange
 * @brief 範囲クラス。
 */
template< class T >
class CRange
{
public:
	/// コンストラクタ。
	CRange( const T& _rtMin, const T& _rtMax )
		: m_tValue( _rtMin )
		, m_tMin( _rtMin )
		, m_tMax( _rtMax )
	{
		ASSERT( _rtMin < _rtMax );
	}
	/// コピーコンストラクタ。
	CRange( const CRange<T>& _rtSrc )
		: m_tValue( _rtSrc.m_tValue )
		, m_tMin( _rtSrc.m_tMin )
		, m_tMax( _rtSrc.m_tMax )
	{
	}
	/// デストラクタ。
	virtual ~CRange(){}

	/// 値を返す。
	T GetValue() const{ return m_tValue; }

	/// 算術演算子のオーバーロード。
	CRange<T>&	operator=( const T& _rtSrc )
	{
		m_tValue = nUtility::Clamp( _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRange<T>& operator+=( const T& _rtSrc )
	{
		m_tValue = nUtility::Clamp( m_tValue + _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRange<T>& operator-=( const T& _rtSrc )
	{
		m_tValue = nUtility::Clamp( m_tValue - _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRange<T>& operator*=( const T& _rtSrc )
	{
		m_tValue = nUtility::Clamp( m_tValue * _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRange<T>& operator/=( const T& _rtSrc )
	{
		m_tValue = nUtility::Clamp( m_tValue / _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRange<T>& operator++()
	{
		m_tValue = nUtility::Clamp( ++m_tValue, m_tMin, m_tMax );
		return *this;
	}
	CRange<T>& operator--( )
	{
		m_tValue = nUtility::Clamp( --m_tValue, m_tMin, m_tMax );
		return *this;
	}

private:
	T	m_tValue;
	T	m_tMin;
	T	m_tMax;
};

/*
 * @class CRangeWrapWrap
 * @brief 範囲クラス。(ラップアラウンド)
 */
template< class T >
class CRangeWrap
{
public:
	/// コンストラクタ。
	CRangeWrap( const T& _rtMin, const T& _rtMax )
		: m_tValue( _rtMin )
		, m_tMin( _rtMin )
		, m_tMax( _rtMax )
	{
		ASSERT( _rtMin < _rtMax );
	}
	/// コピーコンストラクタ。
	CRangeWrap( const CRangeWrap<T>& _rtSrc )
		: m_tValue( _rtSrc.m_tValue )
		, m_tMin( _rtSrc.m_tMin )
		, m_tMax( _rtSrc.m_tMax )
	{
	}
	/// デストラクタ。
	virtual ~CRangeWrap(){}

	/// 値を返す。
	T GetValue() const{ return m_tValue; }

	/// 算術演算子のオーバーロード。
	CRangeWrap<T>&	operator=( const T& _rtSrc )
	{
		m_tValue = nUtility::Wrap( _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRangeWrap<T>& operator+=( const T& _rtSrc )
	{
		m_tValue = nUtility::Wrap( m_tValue + _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRangeWrap<T>& operator-=( const T& _rtSrc )
	{
		m_tValue = nUtility::Wrap( m_tValue - _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRangeWrap<T>& operator*=( const T& _rtSrc )
	{
		m_tValue = nUtility::Wrap( m_tValue * _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRangeWrap<T>& operator/=( const T& _rtSrc )
	{
		m_tValue = nUtility::Wrap( m_tValue / _rtSrc, m_tMin, m_tMax );
		return *this;
	}
	CRangeWrap<T>& operator++()
	{
		m_tValue = nUtility::Wrap( ++m_tValue, m_tMin, m_tMax );
		return *this;
	}
	CRangeWrap<T>& operator--( )
	{
		m_tValue = nUtility::Wrap( --m_tValue, m_tMin, m_tMax );
		return *this;
	}

private:
	T	m_tValue;
	T	m_tMin;
	T	m_tMax;
};


#endif // #ifndef INCLUDE_LIB_UTILITY_RANGE_H