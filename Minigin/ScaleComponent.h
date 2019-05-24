#pragma once
#include "BaseMovementComponent.h"
class ScaleComponent final: public BaseMovementComponent
{
public:
	ScaleComponent() = default;
	virtual ~ScaleComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render()const override;

	void SetScale(const Point2f& s);
	Point2f GetScale() const;

private:
	Point2f m_Scale;

	ScaleComponent(const ScaleComponent&) = delete;
	ScaleComponent(ScaleComponent&&) noexcept = delete;

	ScaleComponent& operator=(const ScaleComponent&) = delete;
	ScaleComponent& operator=(ScaleComponent&&) noexcept = delete;
};

