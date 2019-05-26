#include "pch.h"
#include "HookCommand.h"
#include "TranslationComponent.h"
#include "EventsAndTags.h"
#include "SomeStructs.h"
#include "HookComponent.h"


HookCommand::HookCommand()
	:Command(EVENT::HOOK)
{
}
HookCommand::~HookCommand()
{
}
void HookCommand::Execute()
{
	auto go = GetGameObject();
	Vector2f p = go->GetComponent<TranslationComponent>()->GetDirection();
	auto hook = go->GetComponent<HookComponent>();

	if(!hook->IsLaunched())hook->UseHook(p);
}
