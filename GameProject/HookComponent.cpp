#include "pch.h"
#include "HookComponent.h"

#include "PoolManager.h"

#include "RenderComponent.h"
#include "ColliderComponent.h"
#include "TranslationComponent.h"
#include "SpriteDirectionComponent.h"
#include "TransformComponent.h"
#include "HookCollisionHandler.h"

HookComponent::~HookComponent()
{
	m_pHook = nullptr;

	m_pTrans = nullptr;
	m_pRender = nullptr;
	m_pCollider = nullptr;
}
void* HookComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<HookComponent>();
}
void HookComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<HookComponent>(ptrDelete);
}

void HookComponent::Initialize()
{
	m_pHook = new GameObject();

	m_pRender = new RenderComponent();
	m_pRender->SetTexture("Textures/DigDug/Hook_Sprite.png");
	m_pHook->AddComponent(m_pRender);

	m_pTrans = new TranslationComponent();
	m_pTrans->IsContinuous(true);
	m_pHook->AddComponent(m_pTrans);

	auto spriteDir = new SpriteDirectionComponent();
	spriteDir->SetSpriteComponent(m_pRender);
	spriteDir->SetTranslationComponent(m_pTrans);

	auto c = new ColliderComponent();
	c->SetRectf({ {0.0f, 0.0f}, m_pRender->GetTextureWidth(), m_pRender->GetTextureHeight() });
	c->SetStatic(false);

	auto handler = new HookCollisionHandler();
	c->AddHandler(handler);
	m_pHook->AddComponent(c);

	GetGameObject()->AddChild(m_pHook);

	m_pHook->SetActive(false);
}
void HookComponent::UseHook(const Vector2f& v)
{
	m_pHook->SetActive(true);
	m_pHook->GetTransform()->SetPosition(m_pHook->GetParent()->GetTransform()->GetPosition());

	m_pTrans->SetDirection(v);
	m_pTrans->SetSpeed(20.0f);
	m_pTrans->IsMoving();
}

bool HookComponent::IsLaunched() const
{
	return m_pHook->IsActive();
}
void HookComponent::Update()
{
}
void HookComponent::Render() const
{
}