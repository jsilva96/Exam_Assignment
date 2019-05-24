#include "pch.h"
#include "EnterCommand.h"
#include "EventsAndTags.h"
#include "MenuScene.h"


EnterCommand::EnterCommand()
	:Command(EVENT::ENTER_SELECTION)
{
}
void EnterCommand::Execute()
{
	dynamic_cast<MenuScene*>(GetGameObject()->GetScene())->Select();
}
