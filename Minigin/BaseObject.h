#pragma once
class BaseObject
{
public:
	BaseObject()
	{
		m_IsUsable = true;
		m_IsActive = true;
	}
	virtual ~BaseObject()
	{
		m_IsUsable = false;
		m_IsActive = false;
	}

	bool IsUsable() const { return m_IsUsable; }

	virtual void SetActive(bool isActive) { m_IsActive = isActive; };
	bool IsActive() const { return m_IsActive; };

	BaseObject(const BaseObject&) = delete;
	BaseObject(BaseObject&&) noexcept = delete;

	BaseObject& operator=(const BaseObject&) = delete;
	BaseObject& operator=(BaseObject&&) noexcept = delete;
private:
	static bool m_IsUsable;

	bool m_IsActive = true;


	friend class PoolManager;
	void SetUsable(bool b) { m_IsUsable = b; }
};

