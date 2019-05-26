#include "pch.h"
#include "EnemyManager.h"
#include "SpriteComponent.h"
#include "SpriteDescSwitchComponent.h"
#include "TimerComponent.h"
#include "TransformComponent.h"
#include "PoolManager.h"
#include "PlayerMovementComponent.h"
#include "TranslationComponent.h"
#include "InputComponent.h"
#include "SpriteDirectionComponent.h"
#include "ColliderComponent.h"
#include "EnemyCollisionHandler.h"
#include "EnemySpriteSwitchComponent.h"
#include "FygarSpriteSwitchComponent.h"
#include "EventsAndTags.h"

void* EnemyManager::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<EnemyManager>();
}

void EnemyManager::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<EnemyManager>(ptrDelete);
}

GameObject* EnemyManager::GetFygar(const Point2f& pos, const Vector2f& dir) const
{
	auto go = new GameObject();

	//SPRITE COMPONENT
	SpriteDesc desc;
	desc.width = 13.0f;
	desc.height = 13.0f;
	desc.parseLogic = SpriteParse::HORIZONTAL;
	desc.frames = 2;
	desc.frameTime = 1 / 10.0f;
	desc.startPos = { 0.0f, 0.0f };
	desc.nrOfRuns = -1;

	auto s = new SpriteComponent(desc);
	s->SetTexture("Textures/DigDug/Fygar_Sprite.png");

	go->AddComponent(s);

	//TRANSLATION
	auto trans = new TranslationComponent();
	trans->SetDirection(dir);
	trans->SetSpeed(10.0f);

	go->AddComponent(trans);

	//SPRITE_DESC_SWITCH
	auto pSwitch = new FygarSpriteSwitchComponent();
	pSwitch->SetSpriteComponent(s);
	pSwitch->SetTranslationComponent(trans);

	go->AddComponent(pSwitch);

	//SPRITE_DIRECTION
	auto pDir = new SpriteDirectionComponent();
	pDir->SetSpriteComponent(s);
	pDir->SetTranslationComponent(trans);

	go->AddComponent(pDir);

	//COLLIDER
	auto col = new ColliderComponent();
	col->SetStatic(false);
	col->SetRectf({ pos.x, pos.y, 13.0f, 13.0f });

	auto handler = new EnemyCollisionHandler();
	col->AddHandler(handler);

	go->AddComponent(col);
	go->AddComponent(handler);

	go->SetPosition(pos.x, pos.y);
	go->AddTag(FYGAR);

	return go;
}

GameObject* EnemyManager::GetPooka(const Point2f& pos, const Vector2f& dir) const
{
	auto go = new GameObject();

	//SPRITE COMPONENT
	SpriteDesc desc;
	desc.width = 13.0f;
	desc.height = 12.0f;
	desc.parseLogic = SpriteParse::HORIZONTAL;
	desc.frames = 2;
	desc.frameTime = 1 / 10.0f;
	desc.startPos = { 0.0f, 0.0f };
	desc.nrOfRuns = -1;

	auto s = new SpriteComponent(desc);
	s->SetTexture("Textures/DigDug/Pooka_Sprite.png");

	go->AddComponent(s);

	//TRANSLATION
	auto trans = new TranslationComponent();
	trans->SetDirection(dir);
	trans->SetSpeed(30.0f);

	go->AddComponent(trans);

	//SPRITE_DESC_SWITCH
	auto pSwitch = new EnemySpriteSwitchComponent();
	pSwitch->SetSpriteComponent(s);
	pSwitch->SetTranslationComponent(trans);

	go->AddComponent(pSwitch);

	//SPRITE_DIRECTION
	auto pDir = new SpriteDirectionComponent();
	pDir->SetSpriteComponent(s);
	pDir->SetTranslationComponent(trans);

	go->AddComponent(pDir);

	//COLLIDER
	auto col = new ColliderComponent();
	col->SetStatic(false);
	col->SetRectf({ pos.x, pos.y, 10.0f, 10.0f });

	auto handler = new EnemyCollisionHandler();
	col->AddHandler(handler);

	go->AddComponent(col);
	go->AddComponent(handler);

	go->SetPosition(pos.x, pos.y);

	go->AddTag(POOKA);
	return go;
}

GameObject* EnemyManager::GetPlayableFygar(const Point2f& pos) const
{
	auto go = GetFygar(pos, Vector2f(1.0f, 0.0f));

	auto input = new InputComponent();
	go->AddComponent(input);

	auto plyrMovement = new PlayerMovementComponent(20.0f, 2);
	go->AddComponent(plyrMovement);

	return go;
}

