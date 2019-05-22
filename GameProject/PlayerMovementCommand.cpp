#include "pch.h"
#include "PlayerMovementCommand.h"
#include "TranslationComponent.h"
#include "EventsAndTags.h"

PlayerMovementCommand::PlayerMovementCommand()
	:Command(MOVING), m_TransComponent(nullptr)
{
}
void PlayerMovementCommand::SetDirection(const Vector2f& v)
{
	m_Dir = v;
}
void PlayerMovementCommand::SetSpeed(float f)
{
	m_Speed = f;
}
void PlayerMovementCommand::Execute()
{
	if(!m_TransComponent) return;

	m_TransComponent->SetDirection(m_Dir);
	m_TransComponent->SetSpeed(m_Speed);

	m_TransComponent->IsMoving(true);
}
void PlayerMovementCommand::SetTranslationComponent(TranslationComponent* pComp)
{
	m_TransComponent = pComp;
}
