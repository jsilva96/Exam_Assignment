#include "MiniginPCH.h"
#include "BaseCollisionHandler.h"


BaseCollisionHandler::BaseCollisionHandler()
{
}


BaseCollisionHandler::~BaseCollisionHandler()
{
}

void* BaseCollisionHandler::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<BaseCollisionHandler>();
}

void BaseCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<BaseCollisionHandler>(static_cast<BaseObject*>(ptrDelete));
}