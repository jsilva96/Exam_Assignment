#include "pch.h"
#include "EnemyCollisionHandler.h"
#include "PoolManager.h"

#include "ColliderComponent.h"
#include "EventsAndTags.h"
#include "TranslationComponent.h"
#include "RespawnComponent.h"

void* EnemyCollisionHandler::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<EnemyCollisionHandler>();
}
void EnemyCollisionHandler::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<EnemyCollisionHandler>(ptrDelete);
}
void EnemyCollisionHandler::OnCollideEnter(ColliderComponent* collider)
{
	if(collider->GetGameObject()->CompareTag(TAG::BLOCK) && !collider->GetGameObject()->CompareTag(TAG::DUG_BLOCK))
	{
		auto trans = GetGameObject()->GetComponent<TranslationComponent>();
		trans->MoveBack();
		trans->SetDirection(trans->GetDirection() * -1);
	}
	
	if(collider->GetGameObject()->CompareTag(TAG::PLAYER))
	{
		auto respawn = collider->GetGameObject()->GetComponent<RespawnComponent>();

		if (respawn->CanRespawn()) respawn->Respawn();
		
	}
}
void EnemyCollisionHandler::OnCollideStay(ColliderComponent*)
{
}
void EnemyCollisionHandler::OnCollideExit(ColliderComponent*)
{
}