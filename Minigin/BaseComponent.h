#pragma once
#include "GameObject.h"
#include "BaseObject.h"

class BaseComponent  :  public BaseObject
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent()
	{
		m_pGameObject = nullptr;
	};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() const = 0;

	void SetGameObject(GameObject* obj) { m_pGameObject = obj; };
	GameObject* GetGameObject() const { return m_pGameObject; };
private:
	GameObject* m_pGameObject;

	BaseComponent(const BaseComponent& obj) = delete;
	BaseComponent(BaseComponent&& obj) noexcept = delete;

	BaseComponent& operator=(const BaseComponent& obj) = delete;
	BaseComponent& operator=(BaseComponent&& obj) noexcept = delete;
};