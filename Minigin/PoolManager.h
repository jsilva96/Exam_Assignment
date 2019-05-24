#pragma once

#include <vector>
#include <type_traits>
#include <typeinfo>

#include "BaseObject.h"
#include "ObjectPool.h"

class PoolManager
{
public:
	static PoolManager& GetInstance();
	void Destroy();

	~PoolManager();

	//template<class T = std::enable_if<std::is_base_of<BaseObject, T>::value>::type>
	template<class T>
	T* RetrieveObject()
	{
		if (!std::is_base_of<BaseObject, T>::value)
		{
			return nullptr;
		}
		BaseObject* pObj = GetPool<T>()->RetrieveObject();

		return static_cast<T*>(pObj);
	}

	template<class T>
	void ReturnObject(void* pObj)
	{
		const type_info& ti = typeid(T);

		for (BasePool* pBP : m_Pools)
		{
			if (pBP->GetType() == ti.name())
			{
				pBP->ReturnObject(pObj);
				return;
			}
		}
	}
private:
	PoolManager() = default;
	std::vector<BasePool*> m_Pools;
	static PoolManager* m_pInstance;

	template<class T>
	ObjectPool<T>* GetPool()
	{
		const type_info& ti = typeid(ObjectPool<T>);
		for (BasePool* pB : m_Pools)
		{
			if (pB && typeid(*pB) == ti) return static_cast<ObjectPool<T>*>(pB);
		}
		m_Pools.push_back(new ObjectPool<T>());
		return static_cast<ObjectPool<T>*>(m_Pools.back());
	}
};