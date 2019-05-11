#pragma once
#include "BaseMovementComponent.h"
class RotationComponent : public BaseMovementComponent
{
public:
	RotationComponent();
	virtual ~RotationComponent();

	void Initialize() override;
	void Update() override;
	void Render()const override;

	void Reset() override;

	void SetRotSpeed(const float f);
	float GetRotSpeed() const;

private:
	float m_RotSpeed;

	RotationComponent(const RotationComponent&) = delete;
	RotationComponent(const RotationComponent&&) = delete;

	RotationComponent& operator=(const RotationComponent&) = delete;
	RotationComponent& operator=(const RotationComponent&&) = delete;
};

