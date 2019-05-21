#include "pch.h"
#include "BlockCollisionHandler.h"

#include "PoolManager.h"
#include "ColliderComponent.h"

void* BlockCollisionHandler::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<BlockCollisionHandler>();
}

void BlockCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<BlockCollisionHandler>(static_cast<BaseObject*>(ptrDelete));
}

void BlockCollisionHandler::OnCollideEnter(ColliderComponent* collider)
{
	UNREFERENCED_PARAMETER(collider);
}

void BlockCollisionHandler::OnCollideStay(ColliderComponent* collider)
{
	UNREFERENCED_PARAMETER(collider);
}

void BlockCollisionHandler::OnCollideExit(ColliderComponent* collider)
{
	UNREFERENCED_PARAMETER(collider);
}
