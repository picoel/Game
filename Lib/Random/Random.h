/**
  * @file	Random.h
  * @brief	���������N���X�B
  * @date 2015/04/19 13:01:07
  */

#ifndef INCLUDE_RANDOM_H
#define INCLUDE_RANDOM_H

#include <random>

/*
 * @class	CRandomReal
 * @brief	�����^�̗��������N���X�B
 * @note	�R���X�g���N�^�Ńn�[�h�E�F�A�G���g���s�[�\�[�X����V�[�h�l��ݒ肷�邽�߁A
 *			�����R�X�g�������B���t���[����������悤�Ȏg�����͔����邱�ƁB 
 */
template< typename T >
class CRandomReal
{
public:
	CRandomReal( T _fMin, T _fMax );
	~CRandomReal();

	T GetRandom();

private:
	std::mt19937_64*					m_pcRandomMT;		///< �����Z���k�E�c�C�X�^�[�@�ɂ�闐�������B
	std::uniform_real_distribution<T>*	m_pcDistribution;
};


/*
 * @class	CRandomInt
 * @brief	�����^�̗��������N���X�B
 * @note	�R���X�g���N�^�Ńn�[�h�E�F�A�G���g���s�[�\�[�X����V�[�h�l��ݒ肷�邽�߁A
 *			�����R�X�g�������B���t���[����������悤�Ȏg�����͔����邱�ƁB 
 */
template< typename T >
class CRandomInt
{
public:
	CRandomInt( T _fMin, T _fMax );
	~CRandomInt();

	T GetRandom();

private:
	std::mt19937_64*					m_pcRandomMT;		///< �����Z���k�E�c�C�X�^�[�@�ɂ�闐�������B
	std::uniform_int_distribution<T>*	m_pcDistribution;
};


#include "Lib/Random/RandomReal.h"
#include "Lib/Random/RandomInt.h"

#endif // #ifndef INCLUDE_RANDOM_H