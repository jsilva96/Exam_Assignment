#include "pch.h"
#include "HookCommand.h"
#include "TranslationComponent.h"
#include "EventsAndTags.h"
#include "SomeStructs.h"
#include "HookComponent.h"
#include "TransformComponent.h"

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

	/*if (p == Vector2f(0.0f, 0.0f))
	{
		if (go->GetTransform()->GetRotation() == 0) p.y = 0.0f;
	}*/

	if(!hook->IsLaunched())hook->UseHook(p);
}
