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
	m_Dir = { 0.0f, 0.0f };
	m_Speed = 0.0f;
}
void* TranslationComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<TranslationComponent>();
}
void TranslationComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<TranslationComponent>(static_cast<BaseObject*>(ptrDelete));
}
void TranslationComponent::Initialize()
{
	m_PrevPos = GetGameObject()->GetTransform()->GetPosition();
}
void TranslationComponent::Update()
{
	m_WasMoving = false;
	if (!m_IsMoving) return;

	float elapsedSecs{ 1.0f };
	
	if (m_IsTimeDependent) elapsedSecs = Time::GetInstance().GetElapsedSecs();

	Vector2f v{ m_Dir * m_Speed *elapsedSecs };

	m_PrevPos = GetGameObject()->GetTransform()->GetPosition();
	Point2f p{ m_PrevPos }; 
	p += v;

	GetGameObject()->GetTransform()->SetPosition(p);

	if (!m_IsContinuous)
	{
		m_WasMoving = true;
		m_IsMoving = false;
	}
}
void TranslationComponent::Render() const
{
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
	GetGameObject()->GetTransform()->SetPosition(m_PrevPos);
}
bool TranslationComponent::GetIsMoving() const
{
	return m_IsMoving || m_WasMoving;
}
