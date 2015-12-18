/**
  * @file	RenderContextFactory.h
  * @brief	�`��R���e�L�X�g�����N���X�B
  * @data 2015/11/15 19:35:04
  */

#ifndef INCLUDE_LIB_RENDER_CONTEXT_FACTORY_H
#define INCLUDE_LIB_RENDER_CONTEXT_FACTORY_H

class IRenderContext;

/*
 * @class IRenderContextFactory
 * @brief �`��R���e�L�X�g�����N���X�B
 */
class IRenderContextFactory
{
public:
	/// �R���X�g���N�^�B
	IRenderContextFactory(){}
	/// �f�X�g���N�^�B
	virtual ~IRenderContextFactory(){}

	/// �����B
	virtual IRenderContext*	Create() = 0;
};

#endif // #ifndef INCLUDE_LIB_RENDER_CONTEXT_FACTORY_H
