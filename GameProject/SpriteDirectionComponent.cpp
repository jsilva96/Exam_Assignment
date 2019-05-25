#include "pch.h"
#include "SpriteDirectionComponent.h"

#include "PoolManager.h"
#include "TranslationComponent.h"

SpriteDirectionComponent::~SpriteDirectionComponent()
{
	m_pTrans = nullptr;
	m_Dir = { 0.0f, 0.0f };
}
void* SpriteDirectionComponent::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<SpriteDirectionComponent>();
}
void SpriteDirectionComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<SpriteDirectionComponent>(ptrDelete);
}
void SpriteDirectionComponent::Initialize()
{
	if (!m_pTrans)
	{
		m_pTrans = GetGameObject()->GetComponent<TranslationComponent>();
		if (!m_pTrans) throw std::runtime_error("PlayerMovementComponent::Initialize->No translation component found");
	}
}
void SpriteDirectionComponent::Update()
{
}
void SpriteDirectionComponent::Render() const
{
}
void SpriteDirectionComponent::SetTranslationComponent(TranslationComponent* pComp)
{
	m_pTrans = pComp;
}
