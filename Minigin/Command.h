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
	};

	virtual void Execute() = 0;
	void SetGameObject(GameObject* pObject) 
	{
		m_pGameObject = pObject; 
	};

	unsigned int GetEvent() { return m_Event; };

	protected:
	unsigned int m_Event;
	GameObject* m_pGameObject;

private:
	Command(const Command&) = delete;
	Command(Command&&) noexcept = delete;

	Command& operator=(const Command&) = delete;
	Command& operator=(Command&&) noexcept = delete;
};

