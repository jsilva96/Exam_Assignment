#pragma once
#include "GameObject.h"

class Command  :  public BaseObject
{
public:
	Command(const std::string& event)
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

	std::string GetEvent() { return m_Event; };

	protected:
	std::string m_Event;
	GameObject* m_pGameObject;

private:
	Command(const Command&) = delete;
	Command(Command&&) noexcept = delete;

	Command& operator=(Command&) = delete;
	Command& operator=(Command&&) noexcept = delete;
};

