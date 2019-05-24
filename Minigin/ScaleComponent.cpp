#include "MiniginPCH.h"
#include "ScaleComponent.h"
#include "TransformComponent.h"

ScaleComponent::~ScaleComponent()
{
	m_Scale = { 1.0f, 1.0f };
}

void* ScaleComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<ScaleComponent>();
}
void ScaleComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<ScaleComponent>(ptrDelete);
}
void ScaleComponent::Initialize()
{
}
void ScaleComponent::Update()
{
	if (!m_IsMoving) return;

	float elapsedSecs{ 1.0f };
	if (m_IsTimeDependent) elapsedSecs = Time::GetInstance().GetElapsedSecs();

	Point2f s = GetGameObject()->GetTransform()->GetScale();
	s += (m_Scale * elapsedSecs);

	GetGameObject()->GetTransform()->SetScale(s);

	if (!m_IsContinuous) m_IsMoving = false;
}
void ScaleComponent::Render() const
{
}
void ScaleComponent::SetScale(const Point2f & s)
{
	m_Scale = s;
}
Point2f ScaleComponent::GetScale() const
{
	return m_Scale;
}
