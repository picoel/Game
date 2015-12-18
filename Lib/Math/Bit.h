/**
  * @file	Bit.h
  * @brief	Bit‰‰ŽZŠÖ”B
  * @date 2015/04/22 23:21:04
  */

#ifndef INCLUDE_BIT_H
#define INCLUDE_BIT_H

namespace nBit
{
	inline U32 GetCountBit( U32 _uBit )
	{
		_uBit = ( _uBit & 0x55555555 ) + ( _uBit >> 1 & 0x55555555 );
		_uBit = ( _uBit & 0x33333333 ) + ( _uBit >> 2 & 0x33333333 );
		_uBit = ( _uBit & 0x0f0f0f0f ) + ( _uBit >> 4 & 0x0f0f0f0f );
		_uBit = ( _uBit & 0x00ff00ff ) + ( _uBit >> 8 & 0x00ff00ff );
		return ( _uBit & 0x0000ffff ) + ( _uBit >> 16 & 0x0000ffff );
	}

	inline void GetMaxBit( U32* _puOutIndex, U32 _uBit )
	{
		if (_uBit <= 0)
		{
			return; // failsafe
		}
		_uBit |= _uBit >> 1;
		_uBit |= _uBit >> 2;
		_uBit |= _uBit >> 4;
		_uBit |= _uBit >> 8;
		_uBit |= _uBit >> 16;

		*_puOutIndex = GetCountBit( _uBit ) - 1;
	}

	inline void GetMinBit( U32* _puOutIndex, U32 _uBit )
	{
		if (_uBit <= 0)
		{
			return; // failsafe
		}

		_uBit |= _uBit << 1;
		_uBit |= _uBit << 2;
		_uBit |= _uBit << 4;
		_uBit |= _uBit << 8;
		_uBit |= _uBit << 16;

		*_puOutIndex = 32 - GetCountBit( _uBit );
	}

	inline U32 GetCountBit( U64 _uBit )
	{
		_uBit = ( _uBit & 0x5555555555555555 ) + ( _uBit >> 1 & 0x5555555555555555 );
		_uBit = ( _uBit & 0x3333333333333333 ) + ( _uBit >> 2 & 0x3333333333333333 );
		_uBit = ( _uBit & 0x0f0f0f0f0f0f0f0f ) + ( _uBit >> 4 & 0x0f0f0f0f0f0f0f0f );
		_uBit = ( _uBit & 0x00ff00ff00ff00ff ) + ( _uBit >> 8 & 0x00ff00ff00ff00ff );
		_uBit = ( _uBit & 0x0000ffff0000ffff ) + ( _uBit >> 16 & 0x0000ffff0000ffff );
		return ( _uBit & 0x00000000ffffffff ) + ( _uBit >> 32 & 0x00000000fffffffff );
	}

	inline void GetMaxBit( U32* _puOutIndex, U64 _uBit )
	{
		if (_uBit <= 0)
		{
			return; // failsafe
		}
		_uBit |= _uBit >> 1;
		_uBit |= _uBit >> 2;
		_uBit |= _uBit >> 4;
		_uBit |= _uBit >> 8;
		_uBit |= _uBit >> 16;
		_uBit |= _uBit >> 32;

		*_puOutIndex = GetCountBit( _uBit ) - 1;
	}

	inline void GetMinBit( U32* _puOutIndex, U64 _uBit )
	{
		if (_uBit <= 0)
		{
			return; // failsafe
		}

		_uBit |= _uBit << 1;
		_uBit |= _uBit << 2;
		_uBit |= _uBit << 4;
		_uBit |= _uBit << 8;
		_uBit |= _uBit << 16;
		_uBit |= _uBit << 32;

		*_puOutIndex = 64 - GetCountBit( _uBit );
	}
}

#endif // #ifndef INCLUDE_BIT_H