#pragma once
#include "GameObject.h"

class Command  :  public BaseObject
{
public:
	Command(const std::string& event)
		:m_Event{ event }
	{
	}
	virtual ~Command() {};

	virtual void Execute() = 0;
	void SetGameObject(GameObject* pObject) 
	{
		m_pGameObject = pObject; 
	};
	
	std::string GetEvent() { return m_Event; };

	void Reset() override
	{
		m_pGameObject = nullptr;
	}

protected:
	std::string m_Event;
	GameObject* m_pGameObject;

private:
	Command(const Command& obj) = delete;
	Command(const Command&& obj) = delete;

	Command& operator=(const Command& obj) = delete;
	Command& operator=(const Command&& obj) = delete;
};

