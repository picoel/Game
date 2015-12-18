/**
  * @file	Draw.h
  * @brief	描画を行う基底クラス。
  * @data 2015/11/04 05:00:18
  */

#ifndef INCLUDE_LIB_DRAW_H
#define INCLUDE_LIB_DRAW_H

class IRenderContext;

/*
 * @class CDraw
 * @brief 描画を行う基底クラス。
 */
class CDraw
{
public:
	/// 描画処理。
	virtual void Draw( IRenderContext* _pcRenderContext ){}

	/// アクティブフラグの設定。
	void SetActiveDraw( bool _bActive ){ m_bActive = _bActive; }
	/// アクティブフラグの取得。
	bool IsActiveDraw() const{ return m_bActive; }

	/// 描画レベルの取得。
	U32 GetDrawLv() const{ return m_uDrawLv; }

protected:
	CDraw( U32 _uDrawLv );
	virtual ~CDraw();

private:
	U32		m_uDrawLv;
	bool	m_bActive;
};

#endif // #ifndef INCLUDE_LIB_DRAW_H