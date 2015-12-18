/**
  * @file	Range.h
  * @brief	�͈̓N���X�B
  * @date 2015/06/08 01:04:32
  */
#ifndef INCLUDE_LIB_UTILITY_RANGE_H
#define INCLUDE_LIB_UTILITY_RANGE_H

#include "Lib/Utility/LibUtility.h"
#include "Lib/Debug/Assert.h"

/*
 * @class CRange
 * @brief �͈̓N���X�B
 */
template< class T >
class CRange
{
public:
	/// �R���X�g���N�^�B
	CRange( const T& _rtMin, const T& _rtMax )
		: m_tValue( _rtMin )
		, m_tMin( _rtMin )
		, m_tMax( _rtMax )
	{
		ASSERT( _rtMin < _rtMax );
	}
	/// �R�s�[�R���X�g���N�^�B
	CRange( const CRange<T>& _rtSrc )
		: m_tValue( _rtSrc.m_tValue )
		, m_tMin( _rtSrc.m_tMin )
		, m_tMax( _rtSrc.m_tMax )
	{
	}
	/// �f�X�g���N�^�B
	virtual ~CRange(){}

	/// �l��Ԃ��B
	T GetValue() const{ return m_tValue; }

	/// �Z�p���Z�q�̃I�[�o�[���[�h�B
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
 * @brief �͈̓N���X�B(���b�v�A���E���h)
 */
template< class T >
class CRangeWrap
{
public:
	/// �R���X�g���N�^�B
	CRangeWrap( const T& _rtMin, const T& _rtMax )
		: m_tValue( _rtMin )
		, m_tMin( _rtMin )
		, m_tMax( _rtMax )
	{
		ASSERT( _rtMin < _rtMax );
	}
	/// �R�s�[�R���X�g���N�^�B
	CRangeWrap( const CRangeWrap<T>& _rtSrc )
		: m_tValue( _rtSrc.m_tValue )
		, m_tMin( _rtSrc.m_tMin )
		, m_tMax( _rtSrc.m_tMax )
	{
	}
	/// �f�X�g���N�^�B
	virtual ~CRangeWrap(){}

	/// �l��Ԃ��B
	T GetValue() const{ return m_tValue; }

	/// �Z�p���Z�q�̃I�[�o�[���[�h�B
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