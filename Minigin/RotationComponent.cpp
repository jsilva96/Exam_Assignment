#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "RotationComponent.h"

RotationComponent::~RotationComponent()
{
	m_RotSpeed = 0.0f;
}
void* RotationComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<RotationComponent>();
}
void RotationComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<RotationComponent>(static_cast<BaseObject*>(ptrDelete));
}
void RotationComponent::Initialize()
{
}
void RotationComponent::Update()
{
	if (!m_IsMoving) return;
	auto go = GetGameObject();

	float elapsedSecs{ 1.0f };
	if (m_IsTimeDependent) elapsedSecs = Time::GetInstance().GetElapsedSecs();

	float r = m_RotSpeed * elapsedSecs;

	go->GetTransform()->SetRotation(go->GetTransform()->GetRotation() + r);

	if (!m_IsContinuous) m_IsMoving = false;
}
void RotationComponent::Render() const
{
}
void RotationComponent::SetRotSpeed(const float f)
{
	m_RotSpeed = f;
}
float RotationComponent::GetRotSpeed() const
{
	return m_RotSpeed;
}