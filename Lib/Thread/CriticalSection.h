/**
  * @file	CriticalSection.h
  * @brief	クリティカルセクション制御。
  * @date 2015/05/10 02:57:00
  */

#ifndef INCLUDE_CRITICALSECTION_H
#define INCLUDE_CRITICALSECTION_H

#include "Lib/LibWindows.h"

/*
 * @class	CCriticalSection
 * @brief	クリティカルセクション。
 */
class CCriticalSection
{
public:
	/// コンストラクタ。
	CCriticalSection();
	/// デストラクタ。
	virtual ~CCriticalSection();

	/// クリティカルセクション開始。
	void Enter();
	/// クリティカルセクション終了。
	void Leave();
private:
	CRITICAL_SECTION	m_stCriticalSection;
};

/*
 * @class	CCriticalSectionBlock
 * @brief	ブロック内でクリティカルセクションを開始する。
 * @note	ブロックが終了するまでCCriticalSectionが生存している必要がある。
 */
class CCriticalSectionBlock
{
public:
	/// コンストラクタ。
	CCriticalSectionBlock( CCriticalSection* _pcCriticalSection );
	/// デストラクタ。
	virtual ~CCriticalSectionBlock();

private:
	CCriticalSection*	m_pcCriticalSection;
};

#endif // #ifndef INCLUDE_CRITICALSECTION_H