#pragma once
#include "BaseComponent.h"

class ColliderComponent;
class BaseCollisionHandler : public BaseComponent
{
public:
	BaseCollisionHandler();
	virtual ~BaseCollisionHandler();

	void Initialize() override{}
	void Update() override{};
	void Render() const override{};

	virtual void OnCollideEnter(ColliderComponent* collider) = 0;
	virtual void OnCollideStay(ColliderComponent* collider) = 0;
	virtual void OnCollideExit(ColliderComponent* collider) = 0;

	BaseCollisionHandler(const BaseCollisionHandler&) = delete;
	BaseCollisionHandler(BaseCollisionHandler&&) = delete;

	BaseCollisionHandler& operator=(const BaseCollisionHandler&) = delete;
	BaseCollisionHandler& operator=(BaseCollisionHandler&&) = delete;
};

