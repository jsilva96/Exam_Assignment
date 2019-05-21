#include "pch.h"
#include "PlayerCollisionHandler.h"

#include "PoolManager.h"
#include "ColliderComponent.h"
#include "BlockCollisionHandler.h"
#include "RenderComponent.h"
#include "EventsAndTags.h"

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
	//UNREFERENCED_PARAMETER(collider);
}
void PlayerCollisionHandler::OnCollideStay(ColliderComponent* collider)
{
	UNREFERENCED_PARAMETER(collider);
}
void PlayerCollisionHandler::OnCollideExit(ColliderComponent* collider)
{
	UNREFERENCED_PARAMETER(collider);
}