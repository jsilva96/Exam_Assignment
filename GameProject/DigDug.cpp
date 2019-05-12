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
	InitializePooka();
}
void DigDug::Update()
{
	if(timer->IsTimerOver())
	{
		if(m_Sprite < 6)++m_Sprite;
		else m_Sprite = 0;

		m_pPooka->GetComponent<SpriteComponent>()->SetActive(true);
		m_pPooka->GetComponent<SpriteDescSwitchComponent>()->SetDesc(m_Sprite);
		timer->RestartTimer();
	}


	//TEST!!!!
}
void DigDug::Render() const
{
}
void DigDug::Reset()
{
}
void DigDug::InitializeLevel()
{
	auto go = new GameObject();

	auto r = new RenderComponent();
	r->SetTexture("Levels/DigDug/Level1.png");

	go->AddComponent(r);

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

	timer = new TimerComponent();
	timer->SetTimer(5.0f);

	m_pPlayer->AddComponent(timer);


	m_pPlayer->SetPosition(30.0f, 30.0f);
	m_pPlayer->GetTransform()->SetScale(3.0f);

	Add(m_pPlayer);
}
void DigDug::InitializeFygar()
{
	m_pFygar = new GameObject();

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

	m_pFygar->AddComponent(s);

	//SPRITE_DESC_SWITCH
	SpriteDesc phasingDesc, crushedDesc, hooked1Desc, hooked2Desc, hooked3Desc, hooked4Desc,fireDesc;

	auto descSwitch = new SpriteDescSwitchComponent();
	m_pFygar->AddComponent(descSwitch);
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

	timer = new TimerComponent();
	timer->SetTimer(5.0f);

	m_pFygar->AddComponent(timer);

	m_pFygar->SetPosition(30.0f, 30.0f);
	m_pFygar->GetTransform()->SetScale(3.0f);

	Add(m_pFygar);
}
void DigDug::InitializePooka()
{
	m_pPooka = new GameObject();

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

	m_pPooka->AddComponent(s);

	//SPRITE_DESC_SWITCH
	SpriteDesc phasingDesc, crushedDesc, hooked1Desc, hooked2Desc, hooked3Desc, hooked4Desc;

	auto descSwitch = new SpriteDescSwitchComponent();
	m_pPooka->AddComponent(descSwitch);
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

	timer = new TimerComponent();
	timer->SetTimer(5.0f);

	m_pPooka->AddComponent(timer);

	m_pPooka->SetPosition(30.0f, 30.0f);
	m_pPooka->GetTransform()->SetScale(3.0f);

	Add(m_pPooka);
}