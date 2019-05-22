#include "MiniginPCH.h"
#include "BaseCollisionHandler.h"

void* BaseCollisionHandler::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<BaseCollisionHandler>();
}
void BaseCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<BaseCollisionHandler>(static_cast<BaseObject*>(ptrDelete));
}

void BaseCollisionHandler::OnCollideEnter(ColliderComponent*)
{
}
void BaseCollisionHandler::OnCollideStay(ColliderComponent*)
{
}
void BaseCollisionHandler::OnCollideExit(ColliderComponent*)
{
}
