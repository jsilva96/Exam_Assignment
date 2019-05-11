#include "MiniginPCH.h"
#include "InputComponent.h"
#include "Command.h"
#include "InputManager.h"
#include "Gamepad.h"
#include "PoolManager.h"

bool operator<(InputOptions obj1, InputOptions obj2) { return obj1.controller < obj2.controller; };

InputComponent::InputComponent()
	:m_pGamepad{ PoolManager::GetInstance().RetrieveObject<Gamepad>() }
{
	
}
InputComponent::~InputComponent()
{
}
void InputComponent::Initialize()
{
	m_pGamepad->CheckController();
	m_pGamepad->AssignInput(this);

	InputManager::GetInstance().AddInputComponent(this);

	for (std::pair<const InputOptions, std::vector<Command*>>& p : m_pCommands) for (Command* pC : p.second) pC->SetGameObject(m_pGameObject);
}
void InputComponent::Update()
{
	m_pGamepad->CheckController();
}
void InputComponent::UpdateGamepad()
{
	for (std::pair<const InputOptions, std::vector<Command*>>& p : m_pCommands)
	{
		if (m_pGamepad->IsPressed(static_cast<WORD>(p.first.controller))) for (Command* pC : p.second)  pC->Execute();
	}
}
void InputComponent::UpdateKeyboard()
{
	for (std::pair<const InputOptions, std::vector<Command*>>& p : m_pCommands)
	{
		if (CheckKeyboard(p.first.keyboard)) for (Command* pC : p.second)  pC->Execute();
	}
}
void InputComponent::Render() const
{
}
void InputComponent::Reset()
{
	BaseComponent::Reset();

	for (std::pair<const InputOptions, std::vector<Command*>>& p : m_pCommands)
	{
		for (Command* pC : p.second) PoolManager::GetInstance().ReturnObject(pC);
	}
	PoolManager::GetInstance().ReturnObject(m_pGamepad);

	m_pCommands.clear();
}
void InputComponent::CheckInput()
{
	if(m_pGamepad->IsConnected())UpdateGamepad();
	UpdateKeyboard();
}
void InputComponent::AddCommand(Command* pCommand, InputOptions button)
{
	if (AddCheck(m_pCommands[button], pCommand)) pCommand->SetGameObject(m_pGameObject);
}
Gamepad* InputComponent::GetGamepad() const
{
	return m_pGamepad;
}
bool InputComponent::CheckKeyboard(SDL_Scancode scan)
{
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);

	return pStates[scan];
}
