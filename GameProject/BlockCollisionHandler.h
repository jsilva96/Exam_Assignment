#pragma once
#include "BaseCollisionHandler.h"
class BlockCollisionHandler final: public BaseCollisionHandler
{
public:
	BlockCollisionHandler() = default;
	virtual ~BlockCollisionHandler() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void OnCollideEnter(ColliderComponent* collider) override;
	void OnCollideStay(ColliderComponent* collider) override;
	void OnCollideExit(ColliderComponent* collider) override;

	BlockCollisionHandler(const BlockCollisionHandler&) = delete;
	BlockCollisionHandler(BlockCollisionHandler&&) noexcept = delete;

	BlockCollisionHandler& operator=(const BlockCollisionHandler&) = delete;
	BlockCollisionHandler& operator=(BlockCollisionHandler&&) = delete;
};

