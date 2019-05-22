#include "pch.h"
#include "BlockCollisionHandler.h"

#include "PoolManager.h"
#include "ColliderComponent.h"
#include "EventsAndTags.h"
#include "RenderComponent.h"

void* BlockCollisionHandler::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<BlockCollisionHandler>();
}

void BlockCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<BlockCollisionHandler>(static_cast<BaseObject*>(ptrDelete));
}

void BlockCollisionHandler::OnCollideEnter(ColliderComponent* collider)
{
	if (collider->GetGameObject()->CompareTag(PLAYER)) GetGameObject()->GetComponent<RenderComponent>()->SetActive(true);
	else if(collider->GetGameObject()->CompareTag(BLOCK_CARVER))
	{
		GetGameObject()->AddTag(DUG_BLOCK);
		GetGameObject()->GetComponent<RenderComponent>()->SetActive(true);
	}
}
void BlockCollisionHandler::OnCollideStay(ColliderComponent* collider)
{
	UNREFERENCED_PARAMETER(collider);
}

void BlockCollisionHandler::OnCollideExit(ColliderComponent* collider)
{
	UNREFERENCED_PARAMETER(collider);
}
