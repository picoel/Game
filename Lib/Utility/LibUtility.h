/**
  * @file	LibUtility.h
  * @brief	ユーティリティ
  * @date 2015/05/18 03:36:19
  */

#ifndef INCLUDE_LIB_UTILITY_H
#define INCLUDE_LIB_UTILITY_H

// 配列の要素数を求める。
#define lengthof(Array)	( sizeof( (Array) ) / sizeof( (Array)[0] ) )

// キャストの短縮。
#define s_cast static_cast
#define r_cast reinterpret_cast

// 使用しない変数の明示化。
#define UNUSED(x) (void)(x)

namespace nUtility
{
	/**
	 * @brief		値が大きい方を返す。
	 * @param[in]	_rtValue1	: 比較する値。
	 * @param[in]	_rtValue2	: 比較する値。
	 * @retval		大きい方の値。
	 */
	template< typename T >
	T Max( const T& _rtValue1, const T& _rtValue2 )
	{
		return ( _rtValue1 > _rtValue2 ) ? _rtValue1 : _rtValue2;
	}

	/**
	 * @brief		値が小さい方を返す。
	 * @param[in]	_rtValue1	: 比較する値。
	 * @param[in]	_rtValue2	: 比較する値。
	 * @retval		小さい方の値。
	 */
	template< typename T >
	T Min( const T& _rtValue1, const T& _rtValue2 )
	{
		return ( _rtValue1 < _rtValue2 ) ? _rtValue1 : _rtValue2;
	}

	/**
	 * @brief		値を[_rtMin, _rtMax]の範囲に制限する。
	 * @param[in]	_rtValue		: 値。
	 * @param[in]	_rtMin		: 値。
	 * @param[in]	_rtMax		: 値。
	 * @retval		補正した結果の値。
	 */
	template<typename T>
	T Clamp( const T& _rtValue, const T& _rtMin, const T& _rtMax )
	{
		return Min( Max( _rtValue, _rtMin ), _rtMax );
	}

	/**
	 * @brief		値を[_rtMin, _rtMax]の範囲で補正する(繰り返し)。
	 * @param[in]	_rtValue		: 値。
	 * @param[in]	_rtMin		: 値。
	 * @param[in]	_rtMax		: 値。
	 * @retval		補正した結果の値。
	 */
	template< typename T >
	T Wrap( const T& _rtValue, const T& _rtMin, const T& _rtMax )
	{
		T tRet = _rtValue;
		if (_rtValue < _rtMin)
		{
			tRet = _rtMax - ( _rtMin - _rtValue - 1 ) % ( _rtMax - _rtMin + 1 );
		}
		else if (_rtMax < _rtValue)
		{
			tRet = _rtMin + ( _rtValue - _rtMax - 1 ) % ( _rtMax - _rtMin + 1 );
		}
		return tRet;
	}
}

#endif // #ifndef INCLUDE_UTILITY_H