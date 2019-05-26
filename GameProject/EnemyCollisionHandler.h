#pragma once
#include <BaseCollisionHandler.h>
class EnemyCollisionHandler final: public BaseCollisionHandler
{
public:
	EnemyCollisionHandler() = default;
	virtual ~EnemyCollisionHandler() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void OnCollideEnter(ColliderComponent* collider) override;
	void OnCollideStay(ColliderComponent* collider) override;
	void OnCollideExit(ColliderComponent* collider) override;

	EnemyCollisionHandler(const EnemyCollisionHandler&) = delete;
	EnemyCollisionHandler(EnemyCollisionHandler&&) noexcept = delete;

	EnemyCollisionHandler& operator=(const EnemyCollisionHandler&) = delete;
	EnemyCollisionHandler& operator=(EnemyCollisionHandler&&) noexcept = delete;
};

