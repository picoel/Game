/**
  * @file	MemBlock.cpp
  * @brief	�������u���b�N�N���X�̒�`�B
  * @date	2015/05/02 00:19:21
  */

#include "lib/LibPrecompile.h"
#include "Lib/Memory/MemBlock.h"

/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_uBlockSize	: �u���b�N�T�C�Y�B
 */
CMemBlock::CMemBlock( USize _uBlockSize )
	: m_stMemBlockHeader()
{
	Init( _uBlockSize, nullptr, 0 );
}
/**
 * @brief		�R���X�g���N�^�B
 * @param[in]	_uBlockSize	: �u���b�N�T�C�Y�B
 * @param[in]	_psFile		: �Ăяo�����̃t�@�C�����B
 * @param[in]	_uLine		: �Ăяo�����s���B
 */
CMemBlock::CMemBlock( USize _uBlockSize, const S8* _psFile, U32 _uLine )
	: m_stMemBlockHeader()
{
	Init( _uBlockSize, _psFile, _uLine );
}


/**
 * @brief		�������B
 * @param[in]	_uBlockSize		: �u���b�N�T�C�Y�B
 * @param[in]	_psFile			: �Ăяo�����̃t�@�C�����B
 * @param[in]	_uLine			: �Ăяo�����s���B
 */
void CMemBlock::Init( USize _uBlockSize, const S8* _psFile, U32 _uLine )
{
	m_stMemBlockHeader.Init();
	m_stMemBlockHeader.m_uAllocSize = _uBlockSize - sizeof( StMemBlockHeader ) - sizeof( StMemBlockFooter );

#if defined( USE_MEMORY_DEBUG )
	m_stMemBlockHeader.m_psDebugAllocFile = _psFile;
	m_stMemBlockHeader.m_uDebugAllocLine = _uLine;
#else // #if defined( USE_MEMORY_DEBUG )
	UNUSED( _psFile );
	UNUSED( _uLine );
#endif // #else // #if defined( USE_MEMORY_DEBUG )

	// �t�b�^�[���Z�b�g�B
	U8* const pThis = reinterpret_cast<U8*>( this );
	U8* pFooter = pThis + sizeof( m_stMemBlockHeader ) + m_stMemBlockHeader.m_uAllocSize;

	StMemBlockFooter* pstFooter = new( pFooter ) StMemBlockFooter();
	if (pstFooter)
	{
		pstFooter->Init();
		pstFooter->m_uBlockSize = _uBlockSize;
	}
}
