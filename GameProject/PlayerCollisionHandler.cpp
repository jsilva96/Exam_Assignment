#include "pch.h"
#include "PlayerCollisionHandler.h"

#include "PoolManager.h"
#include "ColliderComponent.h"
#include "BlockCollisionHandler.h"
#include "RenderComponent.h"
#include "PlayerSpriteSwitchComponent.h"
#include "EventsAndTags.h"

void PlayerCollisionHandler::Initialize()
{
	m_pSpriteSwitcher = GetGameObject()->GetComponent<PlayerSpriteSwitchComponent>();
}
void* PlayerCollisionHandler::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<PlayerCollisionHandler>();
}

void PlayerCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<PlayerCollisionHandler>(static_cast<BaseObject*>(ptrDelete));
}
void PlayerCollisionHandler::OnCollideEnter(ColliderComponent* collider)
{
	if(collider->GetGameObject()->CompareTag(BLOCK) && !collider->GetGameObject()->CompareTag(DUG_BLOCK))
	{
		m_pSpriteSwitcher->IsDigging(true);
		collider->GetGameObject()->AddTag(DUG_BLOCK);	
	}
}
void PlayerCollisionHandler::OnCollideStay(ColliderComponent* collider)
{
	if (collider->GetGameObject()->CompareTag(DUG_BLOCK))
	{
		m_pSpriteSwitcher->IsDigging(false);
	}
}
void PlayerCollisionHandler::OnCollideExit(ColliderComponent* collider)
{
	if (collider->GetGameObject()->CompareTag(DUG_BLOCK))
	{
		m_pSpriteSwitcher->IsDigging(false);
	}
}