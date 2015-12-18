/**
* @file		Action.h
* @brief	Actionを行う基底クラス。
* @date		2014/12/26 09:31:56
*/

#ifndef INCLUDE_ACTION_H
#define INCLUDE_ACTION_H

/**
 * @class	CAction
 * @brief	Actionを行う基底クラス。
 */
class CAction
{
public:
	/// 更新処理。
	virtual void Action(){}

	/// アクティブフラグの設定。
	void SetActionActive( bool _bActive ){ m_bActive = _bActive; }
	/// アクティブフラグの取得。
	bool IsActionActive() const{ return m_bActive; }

	/// アクションレベルの取得。
	U32 GetActionLv() const{ return m_uActionLv; }

protected:
	CAction( U32 _uActionLv );
	virtual ~CAction();

private:
	U32		m_uActionLv;
	bool	m_bActive;
};

#endif // #ifndef INCLUDE_ACTION_H
