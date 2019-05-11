#include "pch.h"
#include "SpriteDescSwitchComponent.h"

#include "PoolManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"

void* SpriteDescSwitchComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<SpriteDescSwitchComponent>();
}
void SpriteDescSwitchComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
void SpriteDescSwitchComponent::Initialize()
{
	m_SpriteComponent = GetGameObject()->GetComponent<SpriteComponent>();	
}
void SpriteDescSwitchComponent::Update()
{
}
void SpriteDescSwitchComponent::Render() const
{
}
void SpriteDescSwitchComponent::Reset()
{
}
void SpriteDescSwitchComponent::AddDesc(const SpriteDesc& desc)
{
	AddCheck(m_SpriteDesc, desc);
}
void SpriteDescSwitchComponent::SetDesc(int index)
{
	if (m_SpriteComponent)m_SpriteComponent->SetDesc(m_SpriteDesc[index]);
}