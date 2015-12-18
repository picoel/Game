/**
  * @file	RandomInt.h
  * @brief	�����^�̗��������N���X�B
  * @date	2015/05/11 03:57:49
  */

#include "Lib/Random/Random.h"

#ifndef INLCUDE_RANDOM_INT_H
#define INLCUDE_RANDOM_INT_H

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_fMin	: �����̍ŏ��l�B
 * @param[in]	_fMax	: �����̍ő�l�B
 */
template< typename T >
CRandomInt<T>::CRandomInt( T _fMin, T _fMax )
	: m_pcRandomMT( nullptr )
	, m_pcDistribution( nullptr )
{
	std::random_device cRandDevice;
	m_pcRandomMT = pnew std::mt19937_64( cRandDevice() );
	m_pcDistribution = pnew std::uniform_int_distribution<T>( _fMin, _fMax );
}

/**
 * @brief		�f�X�g���N�^�B
 */
template < typename T >
CRandomInt<T>::~CRandomInt()
{
	P_DELETE( m_pcRandomMT );
	P_DELETE( m_pcDistribution );
}

/**
 * @brief		�������擾�B
 * @retval		�R���X�g���N�^�Ŏw�肵���͈͓��̗����B
 */
template< typename T >
T CRandomInt<T>::GetRandom()
{
	return (*m_pcDistribution)( *m_pcRandomMT );
}

#endif // #ifndef INLCUDE_RANDOM_INT_H
