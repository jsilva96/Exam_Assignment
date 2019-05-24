#pragma once
#include <string>

class BaseObject;
class BasePool
{
public:
	BasePool() = default;
	virtual ~BasePool() = default;

	virtual void ReturnObject(void*) = 0;

	virtual void FindNewIndex() = 0;

protected:
	std::string m_TypeName;

	friend class PoolManager;
	std::string GetType() { return m_TypeName; };

private:
	BasePool(const BasePool&) = delete;
	BasePool(BasePool&&) noexcept = delete;

	BasePool& operator=(const BasePool&) = delete;
	BasePool& operator=(BasePool&&) noexcept = delete;
};

