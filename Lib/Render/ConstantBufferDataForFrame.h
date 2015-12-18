/**
  * @file	ConstantBufferDataForFrame.h
  * @brief	���x���p�̃R���X�^���g�o�b�t�@�[�B
  * @date 2015/09/23 17:06:06
  */

#ifndef INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_FRAME_H
#define INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_FRAME_H

#include "Lib/Render/ConstantBufferData.h"
#include "Lib/Math/Matrix.h"

/*
 * @class CConstantBufferDataForFrame
 * @brief �I�u�W�F�N�g�p�̃R���X�^���g�o�b�t�@�[�B
 */
class CConstantBufferDataForFrame : public IConstantBufferData
{
public:
	/// �R���X�^���g�o�b�t�@�[�\���́B
	struct StConstantBufferData
	{
		StMatrix<F32>	m_stMtxDummy;

		void Init()
		{
			m_stMtxDummy.Init();
		}
	};

public:
	/// �R���X�g���N�^�B
	CConstantBufferDataForFrame();
	/// �f�X�g���N�^�B
	virtual ~CConstantBufferDataForFrame(){}

	/// �f�[�^���擾�B
	virtual const void* GetData() const override{ return &m_stBuffer; }
	/// �f�[�^�T�C�Y���擾�B
	virtual USize GetSize() const override{ return sizeof( m_stBuffer ); }

private:
	StConstantBufferData m_stBuffer;
};

#endif // #ifndef INCLUDE_LIB_RENDER_COSTANT_BUFFER_FOR_FRAME_H
