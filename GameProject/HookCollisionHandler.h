#pragma once
#include <BaseCollisionHandler.h>
class HookCollisionHandler final: public BaseCollisionHandler
{
public:
	HookCollisionHandler() = default;
	virtual ~HookCollisionHandler();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void OnCollideEnter(ColliderComponent* collider) override;
	void OnCollideStay(ColliderComponent* collider) override;
	void OnCollideExit(ColliderComponent* collider) override;

	void RemoveHook() const;

	HookCollisionHandler(const HookCollisionHandler&) = delete;
	HookCollisionHandler(HookCollisionHandler&&) noexcept = delete;

	HookCollisionHandler& operator=(const HookCollisionHandler&) = delete;
	HookCollisionHandler& operator=(HookCollisionHandler&&) noexcept = delete;
private:
	GameObject* m_pHookedEnemy;
};

