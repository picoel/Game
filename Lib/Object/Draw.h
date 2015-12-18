/**
  * @file	Draw.h
  * @brief	�`����s�����N���X�B
  * @data 2015/11/04 05:00:18
  */

#ifndef INCLUDE_LIB_DRAW_H
#define INCLUDE_LIB_DRAW_H

class IRenderContext;

/*
 * @class CDraw
 * @brief �`����s�����N���X�B
 */
class CDraw
{
public:
	/// �`�揈���B
	virtual void Draw( IRenderContext* _pcRenderContext ){}

	/// �A�N�e�B�u�t���O�̐ݒ�B
	void SetActiveDraw( bool _bActive ){ m_bActive = _bActive; }
	/// �A�N�e�B�u�t���O�̎擾�B
	bool IsActiveDraw() const{ return m_bActive; }

	/// �`�惌�x���̎擾�B
	U32 GetDrawLv() const{ return m_uDrawLv; }

protected:
	CDraw( U32 _uDrawLv );
	virtual ~CDraw();

private:
	U32		m_uDrawLv;
	bool	m_bActive;
};

#endif // #ifndef INCLUDE_LIB_DRAW_H