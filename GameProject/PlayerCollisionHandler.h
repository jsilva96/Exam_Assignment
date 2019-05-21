#pragma once
#include <BaseCollisionHandler.h>
class PlayerCollisionHandler final : public BaseCollisionHandler
{
public:
	PlayerCollisionHandler() = default;
	virtual ~PlayerCollisionHandler() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void OnCollideEnter(ColliderComponent* collider) override;
	void OnCollideStay(ColliderComponent* collider) override;
	void OnCollideExit(ColliderComponent* collider) override;

	PlayerCollisionHandler(const PlayerCollisionHandler&) = delete;
	PlayerCollisionHandler(PlayerCollisionHandler&&) noexcept = delete;

	PlayerCollisionHandler& operator=(const PlayerCollisionHandler&) = delete;
	PlayerCollisionHandler& operator=(PlayerCollisionHandler&&) noexcept = delete;
};
