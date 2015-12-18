/**
  * @file	Job.h
  * @brief	WorkerThreadで行う仕事クラス。
  * @date	2015/08/08 02:47:32
  */

#ifndef INCLUDE_LIB_WORKER_JOB_H
#define INCLUDE_LIB_WORKER_JOB_H

/*
 * @class CJob
 * @brief 仕事クラス。
 */
class CJob
{
public:
	/// コンストラクタ。
	CJob() : m_bEnd( false ){}
	/// デストラクタ。
	virtual ~CJob(){}

	/// ワーカースレッドで行う処理。
	virtual void Run(){}

	/// 終了したか。
	bool IsEnd() const{ return m_bEnd; }
	/// 終了したか設定。
	void SetEnd( bool _bEnd ){ m_bEnd = _bEnd; }

private:
	bool	m_bEnd;
};

#endif // #ifndef INCLUDE_LIB_WORKER_JOB_H