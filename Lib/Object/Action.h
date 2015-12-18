/**
* @file		Action.h
* @brief	Action���s�����N���X�B
* @date		2014/12/26 09:31:56
*/

#ifndef INCLUDE_ACTION_H
#define INCLUDE_ACTION_H

/**
 * @class	CAction
 * @brief	Action���s�����N���X�B
 */
class CAction
{
public:
	/// �X�V�����B
	virtual void Action(){}

	/// �A�N�e�B�u�t���O�̐ݒ�B
	void SetActionActive( bool _bActive ){ m_bActive = _bActive; }
	/// �A�N�e�B�u�t���O�̎擾�B
	bool IsActionActive() const{ return m_bActive; }

	/// �A�N�V�������x���̎擾�B
	U32 GetActionLv() const{ return m_uActionLv; }

protected:
	CAction( U32 _uActionLv );
	virtual ~CAction();

private:
	U32		m_uActionLv;
	bool	m_bActive;
};

#endif // #ifndef INCLUDE_ACTION_H
