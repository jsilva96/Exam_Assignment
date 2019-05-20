#pragma once
#include <BaseComponent.h>
class PlayerMovementComponent final : public BaseComponent
{
public:
	PlayerMovementComponent();
	virtual ~PlayerMovementComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	PlayerMovementComponent(const PlayerMovementComponent&) = delete;
	PlayerMovementComponent(PlayerMovementComponent&&) noexcept = delete;

	PlayerMovementComponent& operator=(const PlayerMovementComponent&) = delete;
	PlayerMovementComponent& operator=(const PlayerMovementComponent&&) noexcept = delete;

};

