#include "MiniginPCH.h"
#include "ScaleComponent.h"
#include "TransformComponent.h"

ScaleComponent::ScaleComponent()
	:m_Scale{ 1.0f, 1.0f }
{
}
ScaleComponent::~ScaleComponent()
{
}
void ScaleComponent::Initialize()
{
}
void ScaleComponent::Update()
{
	if (!m_IsMoving) return;

	float elapsedSecs{};

	if (m_IsTimeDependent) elapsedSecs = Time::GetInstance().GetElapsedSecs();
	else elapsedSecs = 1.0f;

	Point2f s = m_pGameObject->GetTransform()->GetScale();
	s += (m_Scale * elapsedSecs);

	m_pGameObject->GetTransform()->SetScale(s);

	if (!m_IsContinuous) m_IsMoving = false;
}
void ScaleComponent::Render() const
{
}
void ScaleComponent::Reset()
{
	BaseMovementComponent::Reset();

	m_Scale = { 1.0f, 1.0f };
}
void ScaleComponent::SetScale(const Point2f & s)
{
	m_Scale = s;
}
Point2f ScaleComponent::GetScale() const
{
	return m_Scale;
}
