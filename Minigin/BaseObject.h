#pragma once
class BaseObject
{
public:
	BaseObject()
		:m_IsUsable(true)
	{
		
	}
	virtual ~BaseObject() = default;

	virtual void Reset() = 0;
	bool IsUsable() const { return m_IsUsable; }

	BaseObject(const BaseObject&) = delete;
	BaseObject(const BaseObject&&) noexcept = delete;

	BaseObject& operator=(const BaseObject&) = delete;
	BaseObject& operator=(const BaseObject&&) noexcept = delete;
protected:

private:
	bool m_IsUsable;

	friend class PoolManager;
	void SetUsable(bool b) { m_IsUsable = b; }
};

