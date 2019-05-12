#pragma once
class BaseObject
{
public:
	BaseObject()
		:m_IsUsable(true)
	{
		
	}
	virtual ~BaseObject()
	{
		m_IsUsable = false;
	}

	bool IsUsable() const { return m_IsUsable; }

	BaseObject(const BaseObject&) = delete;
	BaseObject(BaseObject&&) noexcept = delete;

	BaseObject& operator=(const BaseObject&) = delete;
	BaseObject& operator=(BaseObject&&) noexcept = delete;
private:
	bool m_IsUsable;

	friend class PoolManager;
	void SetUsable(bool b) { m_IsUsable = b; }
};

