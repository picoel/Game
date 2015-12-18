/**
  * @file	Rect.cpp
  * @brief	��`�N���X�B
  * @date 2015/09/10 04:35:58
  */

#include "lib/LibPrecompile.h"

#include "Lib/Rect/Rect.h"

/**
 * @brief	�R���X�g���N�^�B
 */
CRect::CRect()
	: m_fPosX( 0.0f )
	, m_fPosY( 0.0f )
	, m_fWidth( 0.0f )
	, m_fHeight( 0.0f )
{
}

/**
 * @brief		���S���W��ݒ�B
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetPos( F32 _fPosX, F32 _fPosY )
{
	m_fPosX = _fPosX;
	m_fPosY = _fPosY;
}

/**
 * @brief		���S���W���擾�B
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX;
	*_pfPosY = m_fPosY;
}

/**
 * @brief		������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetLeftUpPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX + m_fWidth * 0.5f, _fPosY + m_fHeight * 0.5f );
}

/**
 * @brief		������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetLeftUpPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX - m_fWidth * 0.5f;
	*_pfPosY = m_fPosY - m_fHeight * 0.5f;
}

/**
 * @brief		��������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetCenterUpPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX, _fPosY + m_fHeight * 0.5f );
}

/**
 * @brief		��������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetCenterUpPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX;
	*_pfPosY = m_fPosY - m_fHeight * 0.5f;
}

/**
 * @brief		�E����W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetRightUpPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX - m_fWidth * 0.5f, _fPosY + m_fHeight * 0.5f );
}

/**
 * @brief		�E����W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetRightUpPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX + m_fWidth * 0.5f;
	*_pfPosY = m_fPosY - m_fHeight * 0.5f;
}

/**
 * @brief		���������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetLeftCenterPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX + m_fWidth * 0.5f, _fPosY );
}

/**
 * @brief		���������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetLeftCenterPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX - m_fWidth * 0.5f;
	*_pfPosY = m_fPosY;
}

/**
 * @brief		�E�������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetRightCenterPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX - m_fWidth * 0.5f, _fPosY );
}

/**
 * @brief		�E�������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetRightCenterPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX + m_fWidth * 0.5f;
	*_pfPosY = m_fPosY;
}

/**
 * @brief		�������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetLeftDownPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX + m_fWidth * 0.5f, _fPosY - m_fHeight * 0.5f );
}

/**
 * @brief		�������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetLeftDownPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX - m_fWidth * 0.5f;
	*_pfPosY = m_fPosY + m_fHeight * 0.5f;
}

/**
 * @brief		���������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetCenterDownPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX, _fPosY - m_fHeight * 0.5f );
}

/**
 * @brief		���������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetCenterDownPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX;
	*_pfPosY = m_fPosY + m_fHeight * 0.5f;
}

/**
 * @brief		�E�����W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[in]	_fPosX	: X���W�B
 * @param[in]	_fPosY	: Y���W�B
 */
void CRect::SetRightDownPos( F32 _fPosX, F32 _fPosY )
{
	// ���S���W�ɕϊ��B
	SetPos( _fPosX - m_fWidth * 0.5f, _fPosY - m_fHeight * 0.5f );
}

/**
 * @brief		�E�����W���擾�B(���݂̕��ƍ����ɏ����܂��B)
 * @param[out]	_pfPosX	: X���W�̊i�[��B
 * @param[out]	_pfPosY	: Y���W�̊i�[��B
 */
void CRect::GetRightDownPos( F32* _pfPosX, F32* _pfPosY ) const
{
	ASSERT( _pfPosX );
	if (nullptr == _pfPosX)
	{
		return;	// failsafe
	}

	ASSERT( _pfPosY );
	if (nullptr == _pfPosY)
	{
		return;	// failsafe
	}

	*_pfPosX = m_fPosX + m_fWidth * 0.5f;
	*_pfPosY = m_fPosY + m_fHeight * 0.5f;
}

/**
 * @brief		����ݒ�B
 * @param[in]	_fWidth	: ���B
 */
void CRect::SetWidth( F32 _fWidth )
{
	m_fWidth = _fWidth;
}

/**
 * @brief		�����擾�B
 * @retval		F32	: ���B
 */
F32 CRect::GetWidth() const
{
	return m_fWidth;
}

/**
 * @brief		������ݒ�B
 * @param[in]	_fHeight	: �����B
 */
void CRect::SetHeight( F32 _fHeight )
{
	m_fHeight = _fHeight;
}

/**
 * @brief		�������擾�B
 * @retval		F32	: �����B
 */
F32 CRect::GetHeight() const
{
	return m_fHeight;
}