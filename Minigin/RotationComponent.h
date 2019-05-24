#pragma once
#include "BaseMovementComponent.h"
class RotationComponent final: public BaseMovementComponent
{
public:
	RotationComponent() = default;
	virtual ~RotationComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render()const override;

	void SetRotSpeed(const float f);
	float GetRotSpeed() const;

private:
	float m_RotSpeed{};

	RotationComponent(const RotationComponent&) = delete;
	RotationComponent(RotationComponent&&) noexcept = delete;

	RotationComponent& operator=(const RotationComponent&) = delete;
	RotationComponent& operator=(RotationComponent&&) noexcept = delete;
};

