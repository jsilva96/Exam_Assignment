#include "pch.h"
#include "FygarSpriteSwitchComponent.h"

#include "PoolManager.h"
#include "SpriteComponent.h"
#include "SpriteDescSwitchComponent.h"
#include "TimerComponent.h"

void* FygarSpriteSwitchComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<FygarSpriteSwitchComponent>();
}
void FygarSpriteSwitchComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<FygarSpriteSwitchComponent>(ptrDelete);
}
void FygarSpriteSwitchComponent::Initialize()
{
	auto go = GetGameObject();

	//SPRITE COMPONENT
	SpriteDesc desc;
	desc.width = 13.0f;
	desc.height = 13.0f;
	desc.parseLogic = SpriteParse::HORIZONTAL;
	desc.frames = 2;
	desc.frameTime = 1 / 10.0f;
	desc.startPos = { 0.0f, 0.0f };
	desc.nrOfRuns = -1;

	//SPRITE_DESC_SWITCH
	SpriteDesc phasingDesc, crushedDesc, hooked1Desc, hooked2Desc, hooked3Desc, hooked4Desc, fireDesc;

	m_Switch = new SpriteDescSwitchComponent();
	go->AddComponent(m_Switch);
	m_Switch->AddDesc(desc);

	phasingDesc = SpriteDesc{ {0.0f, 13.0f}, 2, -1, 13.0f, 11.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(phasingDesc);

	crushedDesc = SpriteDesc{ {0.0f, 24.0f}, 1, -1, 13.0f, 7.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(crushedDesc);

	hooked1Desc = SpriteDesc{ {72.0f, 31.0f}, 1, -1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked1Desc);

	hooked2Desc = SpriteDesc{ {48.0f, 31.0f}, 2, -1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked2Desc);

	hooked3Desc = SpriteDesc{ {24.0f, 31.0f}, 3, -1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked3Desc);

	hooked4Desc = SpriteDesc{ {0.0f, 31.0f}, 1, 1, 24.0f, 23.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked4Desc);

	fireDesc = SpriteDesc{ {0.0f, 54.0f}, 2, -1, 13.0f, 13.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(fireDesc);

	m_pTimer = new TimerComponent();
	m_pTimer->SetTimer(1.0f);

	GetGameObject()->AddComponent(m_pTimer);
	m_pTimer->SetActive(false);
}
void FygarSpriteSwitchComponent::Update()
{
	EnemySpriteSwitchComponent::Update();
}
void FygarSpriteSwitchComponent::Render() const
{
}
