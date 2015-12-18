/**
  * @file	Matrix.h
  * @brief	�s�񉉎Z�B
  * @date 2015/09/23 17:49:46
  */

#ifndef INCLUDE_LIB_MATH_MATRIX_H
#define INCLUDE_LIB_MATH_MATRIX_H

#include "Lib/Math/Vector.h"

/*
 * @struct	StMatrix
 * @brief	�s��^�B
 */
template< typename T >
struct StMatrix
{
	union
	{
		T m[ 4 ][ 4 ];
	};

	void Init()
	{
		for (U32 ii = 0; ii < lengthof( m ); ++ii)
		{
			for (U32 jj = 0; jj < lengthof( m[ ii ] ); ++jj)
			{
				m[ ii ][ jj ] = s_cast<T>(0);
			}
		}
	}
};

#endif // #ifndef INCLUDE_LIB_MATH_MATRIX_H