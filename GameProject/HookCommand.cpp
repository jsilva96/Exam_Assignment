#include "pch.h"
#include "HookCommand.h"
#include "TranslationComponent.h"
#include "EventsAndTags.h"
#include "SomeStructs.h"
#include "HookComponent.h"
#include "TransformComponent.h"
#include "PlayerSpriteSwitchComponent.h"
HookCommand::HookCommand()
	:Command(EVENT::HOOK)
{
}
HookCommand::~HookCommand()
{
	m_pPlayer = nullptr;
}
void HookCommand::Execute()
{
	if (!m_pPlayer) m_pPlayer = GetGameObject()->GetComponent<PlayerSpriteSwitchComponent>();

	if (m_pPlayer->GetState() == PlayerState::HOOKED)
	{
		m_pPlayer->PumpEnemy();
	}
	else
	{
		auto go = GetGameObject();
		Vector2f p = go->GetComponent<TranslationComponent>()->GetDirection();
		auto hook = go->GetComponent<HookComponent>();

		if (!hook->IsLaunched())hook->UseHook(p);
	}
}
