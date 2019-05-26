#include "pch.h"
#include "PlayerSpriteSwitchComponent.h"

#include "PoolManager.h"
#include "SpriteComponent.h"
#include "SpriteDescSwitchComponent.h"
#include "TranslationComponent.h"
#include "TransformComponent.h"
#include "Time.h"
#include "SpriteDirectionComponent.h"
#include "EventsAndTags.h"
#include "EnemySpriteSwitchComponent.h"
#include "FygarSpriteSwitchComponent.h"
#include "HookCollisionHandler.h"

PlayerSpriteSwitchComponent::PlayerSpriteSwitchComponent()
	:m_Sprite(nullptr), m_pTrans(nullptr),m_Dir(), m_State(PlayerState::IDLE)
{
}
PlayerSpriteSwitchComponent::~PlayerSpriteSwitchComponent()
{
	m_pTrans = nullptr;
	m_Sprite = nullptr;
	m_Switch = nullptr;
	m_SpriteDir = nullptr;
	m_pEnemy = nullptr;
	m_Handler = nullptr;
}
void* PlayerSpriteSwitchComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<PlayerSpriteSwitchComponent>();
}
void PlayerSpriteSwitchComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<PlayerSpriteSwitchComponent>(ptrDelete);
}
void PlayerSpriteSwitchComponent::Initialize()
{
	auto go = GetGameObject();

	//SPRITE_DESC_SWITCH
	SpriteDesc idleDesc, movingDesc, digDesc ,hookDesc, hookedDesc, crushedDesc, deadDesc;
	idleDesc.width = 14.0f;
	idleDesc.height = 13.0f;
	idleDesc.parseLogic = SpriteParse::HORIZONTAL;
	idleDesc.frames = 1;
	idleDesc.frameTime = 1 / 10.0f;
	idleDesc.startPos = { 0.0f, 0.0f };
	idleDesc.nrOfRuns = -1;

	m_Switch = new SpriteDescSwitchComponent();
	go->AddComponent(m_Switch);
	m_Switch->AddDesc(idleDesc);

	movingDesc = SpriteDesc{ {0.0f, 0.0f}, 2, -1, 14.0f, 13.0f, 1 / 10.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(movingDesc);
	
	digDesc = SpriteDesc{ {0.0f, 13.0f}, 2, -1, 14.0f, 13.0f, 1 / 10.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(digDesc);

	hookDesc = SpriteDesc{ {0.0f, 26.0f}, 1, -1, 16.0f, 12.0f, 1 / 60.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hookDesc);

	hookedDesc = SpriteDesc{ {0.0f, 38.0f}, 2, -1, 16.0f, 13.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(hookedDesc);

	crushedDesc = SpriteDesc{ {0.0f, 51.0f}, 1, -1, 14.0f, 7.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(crushedDesc);

	deadDesc = SpriteDesc{ {0.0f, 58.0f}, 5, 1, 17.0f, 15.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	m_Switch->AddDesc(deadDesc);

	m_SpriteDir = GetGameObject()->GetComponent<SpriteDirectionComponent>();

	if (!m_SpriteDir) throw std::runtime_error("PlayerSpriteSwitchComponent::Initialize->No SpriteDir component found");	
}
void PlayerSpriteSwitchComponent::Update()
{	
	if(m_pEnemy)
	{
		if(m_pEnemy->GetComponent<FygarSpriteSwitchComponent>()->IsEnemyDead())
		{
			m_Handler->RemoveHook();
		}
	}

	if (m_State == PlayerState::HOOK || m_State == PlayerState::HOOKED) return;

	if (!m_pTrans->GetIsMoving())
	{
		SetSpriteIndex(m_IsDigging ? PlayerState::DIGING : PlayerState::IDLE);
	}
	else SetSpriteIndex(m_IsDigging ? PlayerState::DIGING : PlayerState::MOVING);

	if (m_IsDigging)
	{
		m_DugTimer += Time::GetInstance().GetElapsedSecs();
		if (m_DugTimer >= 1.5f)
		{
			m_IsDigging = false;
			m_DugTimer = 0.0f;
		}
	}
}
void PlayerSpriteSwitchComponent::Render() const
{
}
void PlayerSpriteSwitchComponent::SetTranslationComponent(TranslationComponent* pComp)
{
	m_pTrans = pComp;
}
void PlayerSpriteSwitchComponent::SetSpriteComponent(SpriteComponent* pComp)
{
	m_Sprite = pComp;
}

void PlayerSpriteSwitchComponent::SetSpriteIndex(PlayerState s)
{
	m_State = s;
	m_Switch->SetDesc((int)s);

	if (s == PlayerState::HOOK || s == PlayerState::HOOKED)
	{
		m_pTrans->SetActive(false);
		m_SpriteDir->SetActive(false);
	}
	else
	{
		m_pTrans->SetActive(true);
		m_SpriteDir->SetActive(true);
	}
}

void PlayerSpriteSwitchComponent::EnemyHooked(GameObject* pEnemy, HookCollisionHandler* pHandler)
{
	if(!pEnemy)
	{
		m_pEnemy = nullptr;
		return;
	}
	else
	{
		m_pEnemy = pEnemy;
		m_Handler = pHandler;
	}
	if (m_pEnemy->CompareTag(POOKA) || m_pEnemy->CompareTag(FYGAR))
	{
		SetSpriteIndex(PlayerState::HOOKED);
	}
}

void PlayerSpriteSwitchComponent::PumpEnemy()
{
	auto pSpriteSwitch = m_pEnemy->CompareTag(POOKA) ? m_pEnemy->GetComponent<EnemySpriteSwitchComponent>() : m_pEnemy->GetComponent<FygarSpriteSwitchComponent>();
	pSpriteSwitch->Pump();
}
void PlayerSpriteSwitchComponent::IsDigging(bool isDigging)
{
	if (m_IsDigging) return;
	m_IsDigging = isDigging;

	m_DugTimer = 0.0f;
}
