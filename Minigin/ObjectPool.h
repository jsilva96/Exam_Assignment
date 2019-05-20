#pragma once
#include <list>

#include "BaseObject.h"
#include "BasePool.h"
#include "SomeStructs.h"

template<class T>
class ObjectPool : public BasePool
{
public:
	ObjectPool()
		:m_NextIndex(),m_IsPoolFull(false)
	{
		const type_info& ti = typeid(T);
		m_TypeName = ti.name();

		auto tempPool = static_cast<T*>(malloc(sizeof(T) * 100));

		for (size_t i = 0; i < 100; ++i)
		{
			m_ObjectList.push_back(&tempPool[i]);
			m_ActiveObjects.push_back(false);
		}
	}
	virtual ~ObjectPool()
	{
		free(m_ObjectList[0]);
	}

	T* RetrieveObject()
	{
		T* pOb = nullptr;

		if (!m_IsPoolFull)
		{
			pOb = m_ObjectList[m_NextIndex];
			m_ActiveObjects[m_NextIndex] = true;
			FindNewIndex();
		}
		else pOb = static_cast<T*>(malloc(sizeof(T)));
		
		return pOb;
	}
	void FindNewIndex() override
	{
		const auto it = std::find_if(m_ActiveObjects.begin(), m_ActiveObjects.end(), [](bool b) {return !b; });

		m_IsPoolFull = it == m_ActiveObjects.end();
		
		if(!m_IsPoolFull) m_NextIndex = (unsigned int)std::distance(m_ActiveObjects.begin(), it);
	}
private:
	std::vector<T*> m_ObjectList;
	std::vector<bool> m_ActiveObjects;
	unsigned int m_NextIndex;
	bool m_IsPoolFull;

	friend class PoolManager;
	void ReturnObject(BaseObject* pObj) override
	{
		const auto it = std::find(m_ObjectList.begin(), m_ObjectList.end(), pObj);
		if (it == m_ObjectList.end())
		{
			free(pObj);
		}
		else
		{
			if (m_IsPoolFull)
			{
				m_NextIndex = (unsigned int)std::distance(m_ObjectList.begin(), it);
				m_IsPoolFull = false;
			}
			m_ActiveObjects[m_NextIndex] = false;
		}
	}

	ObjectPool(const ObjectPool&) = delete;
	ObjectPool(ObjectPool&&) noexcept = delete;

	ObjectPool& operator=(const ObjectPool&) = delete;
	ObjectPool& operator=(ObjectPool&&) noexcept = delete;
};

