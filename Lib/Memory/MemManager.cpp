/**
  * @file	MemManager.h
  * @brief	�������Ǘ��N���X�B
  * @date 2015/04/19 19:39:32
  */

#include "Lib/LibPrecompile.h"

#include "Lib/Memory/MemManager.h"

// SINGLETONIZE_DECALE�͂��̃N���X�̏���������������܂Ŏg�p�o���Ȃ����߁A���O�Ŏ����B
// SINGLETONIZE_DECALE( CMemManager );
CMemManager* CMemManager::s_pInstance = nullptr;
CMemManager* CMemManager::GetInstance()
{
	return s_pInstance;
}
void CMemManager::CreateInstance()
{
	if( s_pInstance == nullptr )
	{
		s_pInstance = new CMemManager();
	}
}
void CMemManager::DestroyInstance()
{
	delete s_pInstance;
}

/**
 * @brief	�R���X�g���N�^�B
 */
CMemManager::CMemManager()
	: m_pMemAllocator(nullptr)
{
}

/**
 * @brief	�f�X�g���N�^�B
 */
CMemManager::~CMemManager()
{
	Finalize();
}

/**
 * @brief		�������B
 * @param[in]	_uSize	: �������T�C�Y�B
 */
void CMemManager::Initialize( USize _uSize )
{
	ASSERT( nullptr == m_pMemAllocator );
	if (m_pMemAllocator)
	{
		delete( m_pMemAllocator );
	}

	CMemAllocator::StInitParam stInit;
	stInit.Init();
	stInit.m_uSize = _uSize;
	stInit.m_ePartition = CMemAllocator::StInitParam::enPartitionNum_32;

	m_pMemAllocator = new CMemAllocator( stInit );
}

/**
 * @brief	�I�������B
 */
void CMemManager::Finalize()
{
	delete m_pMemAllocator ;
}

/**
 * @brief		�������f�o�b�O���̕\���B
 */
void CMemManager::PrintDebugMemoryInfo() const
{
#if defined( USE_MEMORY_DEBUG )
	ASSERT( m_pMemAllocator );
	if( nullptr == m_pMemAllocator )
	{
		return;	// failsafe
	}
	const CMemAllocator::StDebugMemoryInfo& rstDebugMemoryInfo = m_pMemAllocator->GetDebugMemoryInfo();

	Log( _T("-------- Memory Debug Info --------") );
	Log( _T("Total       : %lld[byte]"), rstDebugMemoryInfo.m_uMemorySizeTotal );
	Log( _T("Used        : %lld[byte]"), rstDebugMemoryInfo.m_uMemorySizeUsed );
	Log( _T("Peek        : %lld[byte]"), rstDebugMemoryInfo.m_uMemorySizePeek );
	Log( _T("Alloc Count : %d"), rstDebugMemoryInfo.m_uCountAlloc );
	Log( _T("Free Count  : %d"), rstDebugMemoryInfo.m_uCountFree );
#endif // #if defined( USE_MEMORY_DEBUG )
}

/**	
 * @brief	�������u���b�N����\���B
 */
void CMemManager::PrintDebugMemoryBlock( bool _bPrintUsed, bool _bPrintFree )
{
#if defined( USE_MEMORY_DEBUG )
	ASSERT( m_pMemAllocator );
	if (nullptr == m_pMemAllocator)
	{
		return;	// failsafe
	}
	m_pMemAllocator->PrintDebugMemBlockInfoAll( _bPrintUsed, _bPrintFree );
#endif // #if defined( USE_MEMORY_DEBUG )
}