#pragma once
#include "BaseComponent.h"
class BaseMovementComponent : public BaseComponent
{
public:
	BaseMovementComponent() = default;
	virtual ~BaseMovementComponent()
	{
	}

	void Initialize() override = 0;
	void Update() override = 0;
	void Render() const override = 0;

	void Reset() override
	{
		BaseComponent::Reset();

		m_IsTimeDependent = true;
		m_IsMoving = false;
		m_IsContinuous = false;
	}

	void IsTimeDependent(bool b = true) { m_IsTimeDependent = b; }
	void IsMoving(bool b = true) { m_IsMoving = b; }
	void IsContinuous(bool b = false) { m_IsContinuous = b; }

protected:
	bool m_IsTimeDependent = true;
	bool m_IsMoving = false;
	bool m_IsContinuous = false;
private:

	BaseMovementComponent(const BaseMovementComponent&) = delete;
	BaseMovementComponent(const BaseMovementComponent&&) = delete;

	BaseMovementComponent& operator=(const BaseMovementComponent&) = delete;
	BaseMovementComponent& operator=(const BaseMovementComponent&&) = delete;
};

