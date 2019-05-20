#include "MiniginPCH.h"
#include "PoolManager.h"

PoolManager* PoolManager::m_pInstance = nullptr;
PoolManager & PoolManager::GetInstance()
{
	if (!m_pInstance) m_pInstance = new PoolManager();
	return *m_pInstance;
}
void PoolManager::Destroy()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
PoolManager::~PoolManager()
{
	DeleteCheck(m_Pools);
}
