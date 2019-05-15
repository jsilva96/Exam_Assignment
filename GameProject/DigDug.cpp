#include "pch.h"
#include "DigDug.h"

#include "PoolManager.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "SpriteDescSwitchComponent.h"
#include "TimerComponent.h"
#include <iostream>
#include "EnemyManager.h"
#include "FPSDisplayComponent.h"
#include "TextComponent.h"

DigDug::DigDug()
{
}
DigDug::~DigDug()
{
}

void* DigDug::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<DigDug>();
}
void DigDug::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}

void DigDug::Initialize()
{
	InitializeLevel();

//	InitializePlayer();
//	InitializeFygar();
//	InitializePooka();
}
void DigDug::Update()
{
}
void DigDug::Render() const
{
}
void DigDug::InitializeLevel()
{
	auto go = new GameObject();

	auto r = new RenderComponent();
	r->SetTexture("Levels/DigDug/Level1.png");

	go->GetTransform()->SetScale(3.0f);
	go->AddComponent(r);

	Add(go);

	go = new GameObject();
	auto fps = new FPSDisplayComponent();
	auto t = new TextComponent();

	fps->SetTextComponent(t);

	go->AddComponent(t);
	go->AddComponent(fps);

	t->SetFont("Lingua.otf", 25);
	t->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });

	Add(go);
}

void DigDug::InitializePlayer()
{
	m_pPlayer = new GameObject();

	//SPRITE COMPONENT
	SpriteDesc desc;
	desc.width = 14.0f;
	desc.height = 13.0f;
	desc.parseLogic = SpriteParse::HORIZONTAL;
	desc.frames = 2;
	desc.frameTime = 1 / 10.0f;
	desc.startPos = { 0.0f, 0.0f};
	desc.nrOfRuns = -1;

	auto s = new SpriteComponent(desc);
	s->SetTexture("Textures/DigDug/Player_Sprite.png");

	m_pPlayer->AddComponent(s);

	//SPRITE_DESC_SWITCH
	SpriteDesc movingDesc, hookDesc, hookedDesc, crushedDesc, deadDesc;
	auto descSwitch = new SpriteDescSwitchComponent();
	m_pPlayer->AddComponent(descSwitch);
	descSwitch->AddDesc(desc);

	movingDesc = SpriteDesc{ {0.0f, 13.0f}, 2, -1, 14.0f, 13.0f, 1 / 10.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(movingDesc);

	hookDesc = SpriteDesc{ {0.0f, 26.0f}, 1, -1, 16.0f, 12.0f, 1 / 10.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hookDesc);

	hookedDesc = SpriteDesc{ {0.0f, 38.0f}, 2, -1, 16.0f, 13.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hookedDesc);

	crushedDesc = SpriteDesc{ {0.0f, 51.0f}, 1, -1, 14.0f, 7.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(crushedDesc);

	deadDesc = SpriteDesc{ {0.0f, 58.0f}, 5, 1, 17.0f, 15.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(deadDesc);

	m_pPlayer->SetPosition(30.0f, 30.0f);
	m_pPlayer->GetTransform()->SetScale(3.0f);

	Add(m_pPlayer);
}

void DigDug::InitializeEnemyManager()
{
	auto go = new GameObject();

	auto r = new EnemyManager();
	go->AddComponent(r);

	Add(go);
}
