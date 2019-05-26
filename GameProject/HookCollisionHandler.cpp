#include "pch.h"
#include "HookCollisionHandler.h"

#include "PoolManager.h"
#include "ColliderComponent.h"
#include "HookComponent.h"
#include "EventsAndTags.h"
#include "TranslationComponent.h"
#include "FygarSpriteSwitchComponent.h"
#include "PlayerSpriteSwitchComponent.h"
HookCollisionHandler::~HookCollisionHandler()
{
	m_pHookedEnemy = nullptr;
}
void* HookCollisionHandler::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<HookCollisionHandler>();
}
void HookCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<HookCollisionHandler>(ptrDelete);
}

void HookCollisionHandler::OnCollideEnter(ColliderComponent* collider)
{
	if (collider->GetGameObject()->CompareTag(TAG::BLOCK) && !collider->GetGameObject()->CompareTag(TAG::DUG_BLOCK)) RemoveHook();

	if(collider->GetGameObject()->CompareTag(TAG::FYGAR) || collider->GetGameObject()->CompareTag(TAG::POOKA))
	{
		m_pHookedEnemy = collider->GetGameObject();
		m_pHookedEnemy->GetComponent<FygarSpriteSwitchComponent>()->SetSpriteIndex((int)EnemyState::HOOKED_1);
		m_pHookedEnemy->GetComponent<TranslationComponent>()->SetActive(false);
		GetGameObject()->GetComponent<TranslationComponent>()->SetActive(false);
		GetGameObject()->GetParent()->GetComponent<PlayerSpriteSwitchComponent>()->EnemyHooked(m_pHookedEnemy);
	}
}
void HookCollisionHandler::OnCollideStay(ColliderComponent*)
{
	/*if (collider->GetGameObject() == GetGameObject()->GetParent())
	{
		GetGameObject()->SetActive(false);
	}*/
}
void HookCollisionHandler::OnCollideExit(ColliderComponent* collider)
{
	if(collider->GetGameObject() == GetGameObject()->GetParent() && !m_pHookedEnemy) RemoveHook();
	
}
void HookCollisionHandler::RemoveHook() const
{
	GetGameObject()->SetActive(false);
	GetGameObject()->GetParent()->GetComponent<HookComponent>()->ResetSprite();
}
