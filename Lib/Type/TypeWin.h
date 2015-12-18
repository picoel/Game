/**
  * @file	TypeWin.h
  * @brief	WindowsópÇÃå^íËã`ÅB
  * @date 2015/03/29 21:37:59
  */

#if defined( _WIN32 ) || defined( _WIN64 )

typedef				char		S8;
typedef unsigned	char		U8;
typedef				short		S16;
typedef	unsigned	short		U16;
typedef				int			S32;
typedef	unsigned	int			U32;
typedef				long long	S64;
typedef	unsigned	long long	U64;
typedef float					F32;
typedef double					F64;

#if defined( _WIN64 )
typedef U64						USize;
#else // #if defined( _WIN64 )
typedef U32						USize;
#endif // #else // #if defined( _WIN64 )

#if defined( _UNICODE )
typedef S16						TChar;
#else // #if defined( _UNICODE )
typedef S8						TChar;
#endif // #else // #if defined( _UNICODE )


#endif // #if defined( WIN32 ) || defined( _WIN64 )
