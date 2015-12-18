/**
  * @file	RandomReal.h
  * @brief	実数型の乱数生成クラス。
  * @date	2015/05/11 03:57:49
  */

#include "Lib/Random/Random.h"

#ifndef INLCUDE_RANDOM_REAL_H
#define INLCUDE_RANDOM_REAL_H

/**
 * @brief		コンストラクタ。
 * @param[in]	_fMin	: 乱数の最小値。
 * @param[in]	_fMax	: 乱数の最大値。
 */
template< typename T >
CRandomReal<T>::CRandomReal( T _fMin, T _fMax )
	: m_pcRandomMT( nullptr )
	, m_pcDistribution( nullptr )
{
	std::random_device cRandDevice;
	m_pcRandomMT = pnew std::mt19937_64( cRandDevice() );
	m_pcDistribution = pnew std::uniform_real_distribution<T>( _fMin, _fMax );
}

/**
 * @brief		デストラクタ。
 */
template < typename T >
CRandomReal<T>::~CRandomReal()
{
	P_DELETE( m_pcRandomMT );
	P_DELETE( m_pcDistribution );
}

/**
 * @brief		乱数を取得。
 * @retval		コンストラクタで指定した範囲内の乱数。
 */
template< typename T >
T CRandomReal<T>::GetRandom()
{
	return (*m_pcDistribution)( *m_pcRandomMT );
}

#endif // #ifndef INLCUDE_RANDOM_REAL_H
