#pragma once
#include "GameObject.h"

class Command : public BaseObject
{
public:
	Command(unsigned int event)
		:m_Event{ event }
	{
	}
	virtual ~Command()
	{
		m_pGameObject = nullptr;
		m_Event = 0;
	};

	virtual void Execute() = 0;

	void SetGameObject(GameObject* pObject) { m_pGameObject = pObject; }
	GameObject* GetGameObject() const { return m_pGameObject; };

	unsigned int GetEvent() { return m_Event; };

	Command(const Command&) = delete;
	Command(Command&&) noexcept = delete;

	Command& operator=(const Command&) = delete;
	Command& operator=(Command&&) noexcept = delete;
private:
	unsigned int m_Event;
	GameObject* m_pGameObject;
};

