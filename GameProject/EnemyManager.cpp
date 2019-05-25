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

void* EnemyManager::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<EnemyManager>();
}

void EnemyManager::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<EnemyManager>(ptrDelete);
}

GameObject* EnemyManager::GetFygar(const Point2f& pos, float scale) const
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

	//SPRITE_DESC_SWITCH
	SpriteDesc phasingDesc, crushedDesc, hooked1Desc, hooked2Desc, hooked3Desc, hooked4Desc, fireDesc;

	auto descSwitch = new SpriteDescSwitchComponent();
	go->AddComponent(descSwitch);
	descSwitch->AddDesc(desc);

	phasingDesc = SpriteDesc{ {0.0f, 13.0f}, 2, -1, 13.0f, 11.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(phasingDesc);

	crushedDesc = SpriteDesc{ {0.0f, 24.0f}, 1, -1, 13.0f, 7.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(crushedDesc);

	hooked1Desc = SpriteDesc{ {72.0f, 31.0f}, 1, -1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked1Desc);

	hooked2Desc = SpriteDesc{ {48.0f, 31.0f}, 2, -1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked2Desc);

	hooked3Desc = SpriteDesc{ {24.0f, 31.0f}, 3, -1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked3Desc);

	hooked4Desc = SpriteDesc{ {0.0f, 31.0f}, 1, 1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked4Desc);

	fireDesc = SpriteDesc{ {0.0f, 54.0f}, 2, -1, 13.0f, 13.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(fireDesc);

	go->SetPosition(pos.x, pos.y);
	go->GetTransform()->SetScale(scale);

	return go;
}

GameObject* EnemyManager::GetPooka(const Point2f& pos, float scale) const
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

	//SPRITE_DESC_SWITCH
	SpriteDesc phasingDesc, crushedDesc, hooked1Desc, hooked2Desc, hooked3Desc, hooked4Desc;

	auto descSwitch = new SpriteDescSwitchComponent();
	go->AddComponent(descSwitch);
	descSwitch->AddDesc(desc);

	phasingDesc = SpriteDesc{ {0.0f, 12.0f}, 2, -1, 13.0f, 8.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(phasingDesc);

	crushedDesc = SpriteDesc{ {0.0f, 20.0f}, 1, -1, 13.0f, 7.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(crushedDesc);

	hooked1Desc = SpriteDesc{ {75.0f, 27.0f}, 1, -1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked1Desc);

	hooked2Desc = SpriteDesc{ {50.0f, 27.0f}, 2, -1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked2Desc);

	hooked3Desc = SpriteDesc{ {25.0f, 27.0f}, 3, -1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked3Desc);

	hooked4Desc = SpriteDesc{ {0.0f, 27.0f}, 1, 1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hooked4Desc);

	go->SetPosition(pos.x, pos.y);
	go->GetTransform()->SetScale(scale);

	return go;
}

GameObject* EnemyManager::GetPlayableFygar(const Point2f& pos) const
{
	auto go = GetFygar(pos, 1.0f);

	auto input = new InputComponent();
	auto trans = new TranslationComponent();
	go->AddComponent(input);
	go->AddComponent(trans);

	auto plyrMovement = new PlayerMovementComponent(20.0f, 2);
	go->AddComponent(plyrMovement);

	return go;
}

