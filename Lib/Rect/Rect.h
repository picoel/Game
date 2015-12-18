/**
  * @file	Rect.h
  * @brief	��`�N���X�B
  * @date 2015/09/10 04:35:58
  */

#ifndef INCLUDE_LIB_RECT_H
#define INCLUDE_LIB_RECT_H

/*
 * @class CRect
 * @brief ��`�N���X�B
 */
class CRect
{
public:
	/// �R���X�g���N�^�B
	CRect();

	/// �f�X�g���N�^�B
	virtual ~CRect(){}

	/// ���S���W��ݒ�B
	void SetPos( F32 _fPosX, F32 _fPosY );
	/// ���S���W���擾�B
	void GetPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// ������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetLeftUpPos( F32 _fPosX, F32 _fPosY );
	/// ������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetLeftUpPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// ��������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetCenterUpPos( F32 _fPosX, F32 _fPosY );
	/// ��������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetCenterUpPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// �E����W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetRightUpPos( F32 _fPosX, F32 _fPosY );
	/// �E����W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetRightUpPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// ���������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetLeftCenterPos( F32 _fPosX, F32 _fPosY );
	/// ���������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetLeftCenterPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// �E�������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetRightCenterPos( F32 _fPosX, F32 _fPosY );
	/// �E�������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetRightCenterPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// �������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetLeftDownPos( F32 _fPosX, F32 _fPosY );
	/// �������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetLeftDownPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// ���������W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetCenterDownPos( F32 _fPosX, F32 _fPosY );
	/// ���������W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetCenterDownPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// �E�����W��ݒ�B(���݂̕��ƍ����ɏ����܂��B)
	void SetRightDownPos( F32 _fPosX, F32 _fPosY );
	/// �E�����W���擾�B(���݂̕��ƍ����ɏ����܂��B)
	void GetRightDownPos( F32* _pfPosX, F32* _pfPosY ) const;

	/// ����ݒ�B
	void SetWidth( F32 _fWidth );
	/// �����擾�B
	F32 GetWidth() const;
	/// ������ݒ�B
	void SetHeight( F32 _fHeight );
	/// �������擾�B
	F32 GetHeight() const;

private:
	F32	m_fPosX;
	F32	m_fPosY;
	F32	m_fWidth;
	F32	m_fHeight;
};

#endif // #ifndef INCLUDE_LIB_RECT_H
