#include "pch.h"
#include "PlayerMovementCommand.h"
#include "TranslationComponent.h"

PlayerMovementCommand::PlayerMovementCommand(const std::string& s)
	:Command(s), m_TransComponent(nullptr)
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
	m_TransComponent->SetDirection(m_Dir);
	m_TransComponent->SetSpeed(m_Speed);

	m_TransComponent->IsMoving(true);
}

void PlayerMovementCommand::SetTranslationComponent(TranslationComponent* pComp)
{
	m_TransComponent = pComp;
}
