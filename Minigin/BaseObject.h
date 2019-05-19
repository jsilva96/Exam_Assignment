#pragma once
class BaseObject
{
public:
	BaseObject()
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
	static bool m_IsUsable;

	friend class PoolManager;
	void SetUsable(bool b) { m_IsUsable = b; }
};

