/**
  * @file	LibUtility.h
  * @brief	���[�e�B���e�B
  * @date 2015/05/18 03:36:19
  */

#ifndef INCLUDE_LIB_UTILITY_H
#define INCLUDE_LIB_UTILITY_H

// �z��̗v�f�������߂�B
#define lengthof(Array)	( sizeof( (Array) ) / sizeof( (Array)[0] ) )

// �L���X�g�̒Z�k�B
#define s_cast static_cast
#define r_cast reinterpret_cast

// �g�p���Ȃ��ϐ��̖������B
#define UNUSED(x) (void)(x)

namespace nUtility
{
	/**
	 * @brief		�l���傫������Ԃ��B
	 * @param[in]	_rtValue1	: ��r����l�B
	 * @param[in]	_rtValue2	: ��r����l�B
	 * @retval		�傫�����̒l�B
	 */
	template< typename T >
	T Max( const T& _rtValue1, const T& _rtValue2 )
	{
		return ( _rtValue1 > _rtValue2 ) ? _rtValue1 : _rtValue2;
	}

	/**
	 * @brief		�l������������Ԃ��B
	 * @param[in]	_rtValue1	: ��r����l�B
	 * @param[in]	_rtValue2	: ��r����l�B
	 * @retval		���������̒l�B
	 */
	template< typename T >
	T Min( const T& _rtValue1, const T& _rtValue2 )
	{
		return ( _rtValue1 < _rtValue2 ) ? _rtValue1 : _rtValue2;
	}

	/**
	 * @brief		�l��[_rtMin, _rtMax]�͈̔͂ɐ�������B
	 * @param[in]	_rtValue		: �l�B
	 * @param[in]	_rtMin		: �l�B
	 * @param[in]	_rtMax		: �l�B
	 * @retval		�␳�������ʂ̒l�B
	 */
	template<typename T>
	T Clamp( const T& _rtValue, const T& _rtMin, const T& _rtMax )
	{
		return Min( Max( _rtValue, _rtMin ), _rtMax );
	}

	/**
	 * @brief		�l��[_rtMin, _rtMax]�͈̔͂ŕ␳����(�J��Ԃ�)�B
	 * @param[in]	_rtValue		: �l�B
	 * @param[in]	_rtMin		: �l�B
	 * @param[in]	_rtMax		: �l�B
	 * @retval		�␳�������ʂ̒l�B
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