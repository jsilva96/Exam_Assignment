#pragma once
#include "BaseMovementComponent.h"
class TranslationComponent : public BaseMovementComponent
{
public:
	TranslationComponent();
	virtual ~TranslationComponent();

	void Initialize() override;
	void Update() override;
	void Render()const override;

	void Reset() override;

	void SetDirection(const Vector2f& v);
	Vector2f GetDirection() const;

	void SetSpeed(const float f);
	float GetSpeed() const;

	void MoveBack();

	bool GetIsMoving() const;

private:
	Vector2f m_Dir;
	float m_Speed;

	Point2f m_PrevPos;

	TranslationComponent(const TranslationComponent&) = delete;
	TranslationComponent(const TranslationComponent&&) = delete;

	TranslationComponent& operator=(const TranslationComponent&) = delete;
	TranslationComponent& operator=(const TranslationComponent&&) = delete;
};

