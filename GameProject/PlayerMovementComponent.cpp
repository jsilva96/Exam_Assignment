#include "pch.h"
#include "PlayerMovementComponent.h"

#include "PoolManager.h"
#include "InputComponent.h"
#include "PlayerMovementCommand.h"
#include "TranslationComponent.h"

PlayerMovementComponent::PlayerMovementComponent(float speed, int plyrNr)
	:m_Speed(speed), m_pInput(nullptr), m_PlyrNr(plyrNr)
{
}
PlayerMovementComponent::~PlayerMovementComponent()
{
	m_pInput = nullptr;
}
void* PlayerMovementComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<PlayerMovementComponent>();
}
void PlayerMovementComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<PlayerMovementComponent>(ptrDelete);
}
void PlayerMovementComponent::Initialize()
{
	if(!m_pInput)
	{
		m_pInput = GetGameObject()->GetComponent<InputComponent>();
		if (!m_pInput) throw std::runtime_error("PlayerMovementComponent::Initialize->No input component found");
	}

	if (!m_pTrans)
	{
		m_pTrans = GetGameObject()->GetComponent<TranslationComponent>();
		if (!m_pTrans) throw std::runtime_error("PlayerMovementComponent::Initialize->No translation component found");
	}

	//LEFT
	InputOptions actions;
	actions.controller = ControllerButton::DPad_Left;
	actions.keyboard = m_PlyrNr == 1 ? KeyboardButton::Left : KeyboardButton::A;

	auto cmd = new PlayerMovementCommand();
	cmd->SetDirection({ -1.0f, 0.0f });
	cmd->SetSpeed(m_Speed);
	cmd->SetTranslationComponent(m_pTrans);

	m_pInput->AddCommand(cmd, actions);


	//RIGHT
	actions.controller = ControllerButton::DPad_Right;
	actions.keyboard = m_PlyrNr == 1 ? KeyboardButton::Right : KeyboardButton::D;

	cmd = new PlayerMovementCommand();
	cmd->SetDirection({ 1.0f, 0.0f });
	cmd->SetSpeed(m_Speed);
	cmd->SetTranslationComponent(m_pTrans);

	m_pInput->AddCommand(cmd, actions);


	//UP
	actions.controller = ControllerButton::DPad_Up;
	actions.keyboard = m_PlyrNr == 1 ? KeyboardButton::Up : KeyboardButton::W;

	cmd = new PlayerMovementCommand();
	cmd->SetDirection({ 0.0f, 1.0f });
	cmd->SetSpeed(m_Speed);
	cmd->SetTranslationComponent(m_pTrans);

	m_pInput->AddCommand(cmd, actions);


	//DOWN
	actions.controller = ControllerButton::DPad_Down;
	actions.keyboard = m_PlyrNr == 1 ? KeyboardButton::Down : KeyboardButton::S;

	cmd = new PlayerMovementCommand();
	cmd->SetDirection({ 0.0f, -1.0f });
	cmd->SetSpeed(m_Speed);
	cmd->SetTranslationComponent(m_pTrans);

	m_pInput->AddCommand(cmd, actions);
}

void PlayerMovementComponent::Update()
{
}

void PlayerMovementComponent::Render() const
{
}
void PlayerMovementComponent::SetInputComponent(InputComponent* pInputComponent)
{
	m_pInput = pInputComponent;
}
void PlayerMovementComponent::SetTranslationComponent(TranslationComponent* pComp)
{
	m_pTrans = pComp;
}
