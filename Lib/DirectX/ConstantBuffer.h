/**
  * @file	ConstantBuffer.h
  * @brief	�R���X�^���g�o�b�t�@�B
  * @data 2015/12/10 04:22:47
  */

#ifndef INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_H
#define INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_H

class IConstantBufferData;
class IRenderContext;

/*
 * @class CConstantBuffer
 * @brief �R���X�^���g�o�b�t�@�B
 */
class CConstantBuffer
{
public:
	/// �R���X�g���N�^�B
	CConstantBuffer( const IConstantBufferData& _rcData );
	/// �f�X�g���N�^�B
	virtual ~CConstantBuffer();

	/// �o�b�t�@���擾�B
	ID3DBuffer*	GetBuffer() const{ return m_pcBuffer; }

private:
	/// �o�b�t�@���쐬�B
	void CreateBuffer( const IConstantBufferData& _rcData );

private:
	ID3DBuffer*	m_pcBuffer;
};

#endif // #ifndef INCLUDE_LIB_DIRECTX_CONSTANTBUFFER_H
