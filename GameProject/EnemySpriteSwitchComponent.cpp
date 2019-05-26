#include "pch.h"
#include "EnemySpriteSwitchComponent.h"

#include "PoolManager.h"
#include "SpriteComponent.h"
#include "SpriteDescSwitchComponent.h"
#include "SpriteDirectionComponent.h"
#include "TimerComponent.h"

EnemySpriteSwitchComponent::~EnemySpriteSwitchComponent()
{
}
void* EnemySpriteSwitchComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<EnemySpriteSwitchComponent>();
}
void EnemySpriteSwitchComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<EnemySpriteSwitchComponent>(ptrDelete);
}
void EnemySpriteSwitchComponent::Initialize()
{
	auto go = GetGameObject();

	SpriteDesc desc;
	desc.width = 13.0f;
	desc.height = 12.0f;
	desc.parseLogic = SpriteParse::HORIZONTAL;
	desc.frames = 2;
	desc.frameTime = 1 / 10.0f;
	desc.startPos = { 0.0f, 0.0f };
	desc.nrOfRuns = -1;

	//SPRITE_DESC_SWITCH
	SpriteDesc phasingDesc, crushedDesc, hooked1Desc, hooked2Desc, hooked3Desc, hooked4Desc;

	m_Switch = new SpriteDescSwitchComponent();
	go->AddComponent(m_Switch);
	m_Switch->AddDesc(desc);

	phasingDesc = SpriteDesc{ {0.0f, 12.0f}, 2, -1, 13.0f, 8.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(phasingDesc);

	crushedDesc = SpriteDesc{ {0.0f, 20.0f}, 1, -1, 13.0f, 7.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(crushedDesc);

	hooked1Desc = SpriteDesc{ {75.0f, 27.0f}, 1, -1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked1Desc);

	hooked2Desc = SpriteDesc{ {50.0f, 27.0f}, 2, -1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked2Desc);

	hooked3Desc = SpriteDesc{ {25.0f, 27.0f}, 3, -1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked3Desc);

	hooked4Desc = SpriteDesc{ {0.0f, 27.0f}, 1, 1, 25.0f, 20.0f, 1, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hooked4Desc);

	m_pTimer = new TimerComponent();
	m_pTimer->SetTimer(0.5f);

	GetGameObject()->AddComponent(m_pTimer);
	m_pTimer->SetActive(false);
}
void EnemySpriteSwitchComponent::Update()
{
	if (m_pTimer->IsActive())
	{
		if (m_pTimer->IsTimerOver())
		{
			if(m_State == (unsigned int)EnemyState::HOOKED_4)
			{
				GetGameObject()->SetActive(false);
				return;
			}
			if (m_State < (unsigned int)EnemyState::HOOKED_1)m_pTimer->RestartTimer();
			else m_pTimer->SetActive(false);

			SetSpriteIndex(m_State - 1);
		}
	}
}
void EnemySpriteSwitchComponent::Render() const
{
}
void EnemySpriteSwitchComponent::Pump()
{
	if (m_State < (unsigned int)EnemyState::HOOKED_1 || m_State >(unsigned int)EnemyState::HOOKED_4) return;

	SetSpriteIndex(m_State + 1);

	if (m_State == (unsigned int)EnemyState::HOOKED_4) m_pTimer->SetActive(true);
}
void EnemySpriteSwitchComponent::SetTranslationComponent(TranslationComponent* pComp)
{
	m_pTrans = pComp;
}
void EnemySpriteSwitchComponent::SetSpriteComponent(SpriteComponent* pComp)
{
	m_Sprite = pComp;
}
void EnemySpriteSwitchComponent::SetSpriteIndex(int index)
{
	if (index == (int)m_State) return;

	if (m_Switch)
	{
		m_State = index;
		m_Switch->SetDesc(index);

		if (m_State >= (unsigned int)EnemyState::HOOKED_1 && m_State <=(unsigned int)EnemyState::HOOKED_4)
		{
			m_pTimer->SetActive(true);
			m_pTimer->RestartTimer();
		}
	}
}