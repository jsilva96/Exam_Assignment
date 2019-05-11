#include "MiniginPCH.h"
#include "TranslationComponent.h"
#include "TransformComponent.h"
#include "Time.h"


TranslationComponent::TranslationComponent()
	:m_Dir{},
	m_Speed{},
	m_PrevPos{}
{
}
TranslationComponent::~TranslationComponent()
{
}
void TranslationComponent::Initialize()
{
	m_PrevPos = m_pGameObject->GetTransform()->GetPosition();
}
void TranslationComponent::Update()
{
	if (!m_IsMoving) return;

	float elapsedSecs{};
	
	if (m_IsTimeDependent) elapsedSecs = Time::GetInstance().GetElapsedSecs();
	else elapsedSecs = 1.0f;

	Vector2f v{};
	v = m_Dir * m_Speed;
	v *= elapsedSecs;

	m_PrevPos = m_pGameObject->GetTransform()->GetPosition();
	Point2f p{ m_PrevPos }; 
	p += v;

	m_pGameObject->GetTransform()->SetPosition(p);

	if (!m_IsContinuous) m_IsMoving = false;
}
void TranslationComponent::Render() const
{
}
void TranslationComponent::Reset()
{
	BaseMovementComponent::Reset();

	m_Dir = { 0.0f, 0.0f };
	m_Speed = 0.0f;
}
void TranslationComponent::SetDirection(const Vector2f & v)
{
	m_Dir = v;
}
Vector2f TranslationComponent::GetDirection() const
{
	return m_Dir;
}
void TranslationComponent::SetSpeed(const float f)
{
	m_Speed = f;
}
float TranslationComponent::GetSpeed() const
{
	return m_Speed;
}
void TranslationComponent::MoveBack()
{
	m_pGameObject->GetTransform()->SetPosition(m_PrevPos);
}

bool TranslationComponent::GetIsMoving() const
{
	return m_IsMoving;
}
