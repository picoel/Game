/**
  * @file	Random.h
  * @brief	乱数生成クラス。
  * @date 2015/04/19 13:01:07
  */

#ifndef INCLUDE_RANDOM_H
#define INCLUDE_RANDOM_H

#include <random>

/*
 * @class	CRandomReal
 * @brief	実数型の乱数生成クラス。
 * @note	コンストラクタでハードウェアエントロピーソースからシード値を設定するため、
 *			生成コストが高い。毎フレーム生成するような使い方は避けること。 
 */
template< typename T >
class CRandomReal
{
public:
	CRandomReal( T _fMin, T _fMax );
	~CRandomReal();

	T GetRandom();

private:
	std::mt19937_64*					m_pcRandomMT;		///< メルセンヌ・ツイスター法による乱数生成。
	std::uniform_real_distribution<T>*	m_pcDistribution;
};


/*
 * @class	CRandomInt
 * @brief	整数型の乱数生成クラス。
 * @note	コンストラクタでハードウェアエントロピーソースからシード値を設定するため、
 *			生成コストが高い。毎フレーム生成するような使い方は避けること。 
 */
template< typename T >
class CRandomInt
{
public:
	CRandomInt( T _fMin, T _fMax );
	~CRandomInt();

	T GetRandom();

private:
	std::mt19937_64*					m_pcRandomMT;		///< メルセンヌ・ツイスター法による乱数生成。
	std::uniform_int_distribution<T>*	m_pcDistribution;
};


#include "Lib/Random/RandomReal.h"
#include "Lib/Random/RandomInt.h"

#endif // #ifndef INCLUDE_RANDOM_H