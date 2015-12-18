/**
  * @file	ConstantBuffer.h
  * @brief	コンスタントバッファ。
  * @data 2015/12/10 04:22:47
  */

#ifndef INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_H
#define INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_H

class IConstantBufferData;
class IRenderContext;

/*
 * @class CConstantBuffer
 * @brief コンスタントバッファ。
 */
class CConstantBuffer
{
public:
	/// コンストラクタ。
	CConstantBuffer( const IConstantBufferData& _rcData );
	/// デストラクタ。
	virtual ~CConstantBuffer();

	/// バッファを取得。
	ID3DBuffer*	GetBuffer() const{ return m_pcBuffer; }

private:
	/// バッファを作成。
	void CreateBuffer( const IConstantBufferData& _rcData );

private:
	ID3DBuffer*	m_pcBuffer;
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_H
