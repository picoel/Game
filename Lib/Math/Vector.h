/**
  * @file	Vector.h
  * @brief	ベクトル演算。
  * @date 2015/09/23 17:28:51
  */

#ifndef INCLUDE_LIB_MATH_VECTOR_H
#define INCLUDE_LIB_MATH_VECTOR_H

/*
 * @struct	StVector2D
 * @brief	2次元ベクトル型。
 */
template< typename T >
struct StVector2D
{
	union
	{
		T	v[ 2 ];

		struct
		{
			T	x;
			T	y;
		};
	};

	void Init()
	{
		x = s_cast<T>(0);
		y = s_cast<T>(0);
	}
};

/*
 * @struct	StVector3D
 * @brief	3次元ベクトル型。
 */
template< typename T >
struct StVector3D
{
	union
	{
		T	v[ 3 ];

		struct
		{
			T	x;
			T	y;
			T	z;
		};

		struct
		{
			T	r;
			T	g;
			T	b;
		};
	};
	void Init()
	{
		x = s_cast<T>( 0 );
		y = s_cast<T>( 0 );
		z = s_cast<T>( 0 );
	}
};

/*
 * @struct	StVector4D
 * @brief	4次元ベクトル型。
 */
template< typename T >
struct StVector4D
{
	union
	{
		T	v[ 4 ];

		struct
		{
			T	x;
			T	y;
			T	z;
			T	w;
		};

		struct
		{
			T	r;
			T	g;
			T	b;
			T	a;
		};
	};

	void Init()
	{
		x = s_cast<T>( 0 );
		y = s_cast<T>( 0 );
		z = s_cast<T>( 0 );
		w = s_cast<T>( 0 );
	}
};


#endif // #ifndef INCLUDE_LIB_MATH_VECTOR_H
