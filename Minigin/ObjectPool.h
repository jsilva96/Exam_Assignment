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
			++m_NextIndex;
		}
		if (!pOb)throw std::exception("Pool is full");

		return pOb;
	}
private:
	std::vector<T*> m_ObjectList;
	unsigned int m_NextIndex;

	friend class PoolManager;
	void ReturnObject(BaseObject* pObj)
	{
		pObj->Reset();
	}


	ObjectPool(const ObjectPool&) = delete;
	ObjectPool(const ObjectPool&&) = delete;

	ObjectPool& operator=(const ObjectPool&) = delete;
	ObjectPool& operator=(const ObjectPool&&) = delete;
};

