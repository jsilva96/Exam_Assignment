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
		:m_NextIndex()
	{
		const type_info& ti = typeid(T);
		m_TypeName = ti.name();

		auto tempPool = static_cast<T*>(malloc(sizeof(T) * 100));

		for (size_t i = 0; i < 100; ++i)
		{
			m_ObjectList.push_back(&tempPool[i]);
		}
	}
	virtual ~ObjectPool()
	{
		free(m_ObjectList[0]);
	}

	T* RetrieveObject()
	{		
		T* pOb = nullptr;

		if (m_NextIndex < m_ObjectList.size())
		{
			pOb = m_ObjectList[m_NextIndex];

			for (size_t i = 0; i < m_ObjectList.size(); ++i)
			{
				if (!static_cast<BaseObject>(m_ObjectList[i]).IsUsable() && (pOb != m_ObjectList[i]))
				{
					m_NextIndex = i;
					break;
				}
			}
		}
		else pOb = malloc(sizeof(T));

		return pOb;
	}
private:
	std::vector<T*> m_ObjectList;
	unsigned int m_NextIndex;

	friend class PoolManager;
	void ReturnObject(BaseObject* pObj) override
	{
		if(std::find(m_ObjectList.begin(), m_ObjectList.end(),pObj) == m_ObjectList.end()) free(pObj);
	}


	ObjectPool(const ObjectPool&) = delete;
	ObjectPool(ObjectPool&&) noexcept = delete;

	ObjectPool& operator=(const ObjectPool&) = delete;
	ObjectPool& operator=(ObjectPool&&) noexcept = delete;
};

