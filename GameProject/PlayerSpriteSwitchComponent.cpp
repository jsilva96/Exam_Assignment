#include "pch.h"
#include "PlayerSpriteSwitchComponent.h"

#include "PoolManager.h"
#include "SpriteComponent.h"
#include "SpriteDescSwitchComponent.h"
#include "TranslationComponent.h"
#include "TransformComponent.h"
PlayerSpriteSwitchComponent::PlayerSpriteSwitchComponent()
	:m_Sprite(nullptr), m_pTrans(nullptr),m_Dir()
{
}
PlayerSpriteSwitchComponent::~PlayerSpriteSwitchComponent()
{
	m_pTrans = nullptr;
	m_Sprite = nullptr;
}
void* PlayerSpriteSwitchComponent::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<PlayerSpriteSwitchComponent>();
}
void PlayerSpriteSwitchComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<PlayerSpriteSwitchComponent>(static_cast<BaseObject*>(ptrDelete));
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

	auto descSwitch = new SpriteDescSwitchComponent();
	go->AddComponent(descSwitch);
	descSwitch->AddDesc(idleDesc);

	movingDesc = SpriteDesc{ {0.0f, 0.0f}, 2, -1, 14.0f, 13.0f, 1 / 10.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(movingDesc);
	
	digDesc = SpriteDesc{ {0.0f, 13.0f}, 2, -1, 14.0f, 13.0f, 1 / 10.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(digDesc);

	hookDesc = SpriteDesc{ {0.0f, 26.0f}, 1, -1, 16.0f, 12.0f, 1 / 10.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hookDesc);

	hookedDesc = SpriteDesc{ {0.0f, 38.0f}, 2, -1, 16.0f, 13.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(hookedDesc);

	crushedDesc = SpriteDesc{ {0.0f, 51.0f}, 1, -1, 14.0f, 7.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(crushedDesc);

	deadDesc = SpriteDesc{ {0.0f, 58.0f}, 5, 1, 17.0f, 15.0f, 1 / 5.0f, SpriteParse::HORIZONTAL };
	descSwitch->AddDesc(deadDesc);
}
void PlayerSpriteSwitchComponent::Update()
{
	if(m_Dir != m_pTrans->GetDirection())
	{
		m_Dir = m_pTrans->GetDirection();

		m_pTrans->GetGameObject()->GetTransform()->SetRotation(m_Dir.x > 0.0f ? 0.0f : m_Dir.y * 90.0f);
		m_Sprite->SetFlipped(m_Dir.x > 0.0f ? false : true, false);
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
