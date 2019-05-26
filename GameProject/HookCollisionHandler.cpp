#include "pch.h"
#include "HookCollisionHandler.h"

#include "PoolManager.h"
#include "ColliderComponent.h"
void* HookCollisionHandler::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<HookCollisionHandler>();
}
void HookCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<HookCollisionHandler>(ptrDelete);
}

void HookCollisionHandler::OnCollideEnter(ColliderComponent*)
{
	/*if (collider->GetGameObject() == GetGameObject()->GetParent())
	{
		GetGameObject()->SetActive(false);
	}*/
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
		GetGameObject()->SetActive(false);
	}
}
