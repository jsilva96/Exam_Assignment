#include "pch.h"
#include "SpriteDirectionComponent.h"

#include "PoolManager.h"
#include "TranslationComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

SpriteDirectionComponent::~SpriteDirectionComponent()
{
	m_pTrans = nullptr;
	m_pSprite = nullptr;
	m_Dir = { 0.0f, 0.0f };
}
void* SpriteDirectionComponent::operator new(size_t)
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

	if (!m_pSprite)
	{
		m_pSprite = GetGameObject()->GetComponent<RenderComponent>();
		if (!m_pSprite)m_pSprite = GetGameObject()->GetComponent<SpriteComponent>();
		if (!m_pSprite) throw std::runtime_error("PlayerMovementComponent::Initialize->No translation component found");
	}
}
void SpriteDirectionComponent::Update()
{
	if (m_Dir != m_pTrans->GetDirection())
	{
		m_Dir = m_pTrans->GetDirection();

		m_pTrans->GetGameObject()->GetTransform()->SetRotation(m_Dir.x > 0.0f ? 0.0f : m_Dir.y * 90.0f);
		m_pSprite->SetFlipped(!(m_Dir.x > 0.0f), m_Dir.y > 0.0f);
	}
}
void SpriteDirectionComponent::Render() const
{
}
void SpriteDirectionComponent::SetTranslationComponent(TranslationComponent* pComp)
{
	m_pTrans = pComp;
}
void SpriteDirectionComponent::SetSpriteComponent(RenderComponent* pComp)
{
	m_pSprite = pComp;
}
