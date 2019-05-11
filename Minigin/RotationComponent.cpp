#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "RotationComponent.h"


RotationComponent::RotationComponent()
	:m_RotSpeed{}
{
}
RotationComponent::~RotationComponent()
{
}
void RotationComponent::Initialize()
{
}
void RotationComponent::Update()
{
	if (!m_IsMoving) return;

	float elapsedSecs{};

	if (m_IsTimeDependent) elapsedSecs = Time::GetInstance().GetElapsedSecs();
	else elapsedSecs = 1.0f;

	float r = m_RotSpeed * elapsedSecs;

	m_pGameObject->GetTransform()->SetRotation(m_pGameObject->GetTransform()->GetRotation() + r);

	if (!m_IsContinuous) m_IsMoving = false;
}
void RotationComponent::Render() const
{
}
void RotationComponent::Reset()
{
	BaseMovementComponent::Reset();

	m_RotSpeed = 0.0f;
}
void RotationComponent::SetRotSpeed(const float f)
{
	m_RotSpeed = f;
}
float RotationComponent::GetRotSpeed() const
{
	return m_RotSpeed;
}