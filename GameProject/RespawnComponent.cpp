#include "pch.h"
#include "RespawnComponent.h"

#include "PoolManager.h"
#include "TransformComponent.h"
RespawnComponent::RespawnComponent(unsigned int nrOfLives)
	:m_Lives(nrOfLives), m_RespawnPos()
{
}
RespawnComponent::~RespawnComponent()
{
	m_Lives = 0;
	m_RespawnPos = {};
}
void* RespawnComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<RespawnComponent>();
}
void RespawnComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<RespawnComponent>(ptrDelete);
}
void RespawnComponent::Initialize()
{
}
void RespawnComponent::Update()
{
}
void RespawnComponent::Render() const
{
}
void RespawnComponent::Respawn()
{
	if (!CanRespawn()) return;

	GetGameObject()->GetTransform()->SetPosition(m_RespawnPos);
	--m_Lives;
}
bool RespawnComponent::CanRespawn() const
{
	return m_Lives != 0;
}
