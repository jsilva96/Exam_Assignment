#pragma once
#include "BaseMovementComponent.h"
class ScaleComponent : public BaseMovementComponent
{
public:
	ScaleComponent();
	virtual ~ScaleComponent();

	void Initialize() override;
	void Update() override;
	void Render()const override;

	void Reset() override;

	void SetScale(const Point2f& s);
	Point2f GetScale() const;

private:
	Point2f m_Scale;

	ScaleComponent(const ScaleComponent&) = delete;
	ScaleComponent(const ScaleComponent&&) = delete;

	ScaleComponent& operator=(const ScaleComponent&) = delete;
	ScaleComponent& operator=(const ScaleComponent&&) = delete;
};

