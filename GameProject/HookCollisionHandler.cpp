#include "pch.h"
#include "HookCollisionHandler.h"

#include "PoolManager.h"
#include "ColliderComponent.h"
#include "HookComponent.h"
#include "EventsAndTags.h"

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
	if (collider->GetGameObject()->CompareTag(TAG::BLOCK) && !collider->GetGameObject()->CompareTag(TAG::DUG_BLOCK))
	{
		RemoveHook();
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
	if(collider->GetGameObject() == GetGameObject()->GetParent())
	{
		RemoveHook();
	}
}
void HookCollisionHandler::RemoveHook() const
{
	GetGameObject()->SetActive(false);
	GetGameObject()->GetParent()->GetComponent<HookComponent>()->ResetSprite();
}
