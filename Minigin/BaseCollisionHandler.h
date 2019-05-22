#pragma once
#include "BaseComponent.h"

class ColliderComponent;
class BaseCollisionHandler : public BaseComponent
{
public:
	BaseCollisionHandler() = default;
	virtual ~BaseCollisionHandler() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override{}
	void Update() override{};
	void Render() const override{};

	virtual void OnCollideEnter(ColliderComponent* collider);
	virtual void OnCollideStay(ColliderComponent* collider);
	virtual void OnCollideExit(ColliderComponent* collider);

	BaseCollisionHandler(const BaseCollisionHandler&) = delete;
	BaseCollisionHandler(BaseCollisionHandler&&) = delete;

	BaseCollisionHandler& operator=(const BaseCollisionHandler&) = delete;
	BaseCollisionHandler& operator=(BaseCollisionHandler&&) = delete;
};

