#pragma once
#include "GameObject.h"
#include "BaseObject.h"

class BaseComponent  :  public BaseObject
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent()
	{
	};
	
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() const = 0;

	virtual void Reset() 
	{
		m_pGameObject = nullptr;
	};

	void SetGameObject(GameObject* obj) { m_pGameObject = obj; };
	
	GameObject* GetGameObject() const { return m_pGameObject; };
protected:
	GameObject* m_pGameObject;

private:
	BaseComponent(const BaseComponent& obj) = delete;
	BaseComponent(BaseComponent&& obj) noexcept = delete;

	BaseComponent& operator=(const BaseComponent& obj) = delete;
	BaseComponent& operator=(BaseComponent&& obj) noexcept = delete;
};