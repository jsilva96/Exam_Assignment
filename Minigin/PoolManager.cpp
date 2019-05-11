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
void PoolManager::ReturnObject(BaseObject* pObj)
{
	const type_info& ti = typeid(*pObj);

	for (BasePool* pBP : m_Pools)
	{
		if (pBP->GetType() == ti.name())
		{
			pBP->ReturnObject(pObj);
			pObj->SetUsable(false);
			return;
		}
	}
}
