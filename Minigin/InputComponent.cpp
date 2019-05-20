#include "MiniginPCH.h"
#include "InputComponent.h"
#include "Command.h"
#include "InputManager.h"
#include "Gamepad.h"
#include "PoolManager.h"

bool operator<(InputOptions obj1, InputOptions obj2) { return obj1.controller < obj2.controller; };

InputComponent::InputComponent()
	:m_pGamepad{ new Gamepad() }
{
	
}
InputComponent::~InputComponent()
{
	for (std::pair<const InputOptions, std::vector<Command*>>& p : m_pCommands)
	{
		for (Command* pC : p.second) DeleteCheck(pC);
	}
	DeleteCheck(m_pGamepad);

	m_pCommands.clear();
}
void* InputComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<InputComponent>();
}
void InputComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<InputComponent>(static_cast<BaseObject*>(ptrDelete));
}
void InputComponent::Initialize()
{
	m_pGamepad->CheckController();
	m_pGamepad->AssignInput(this);

	InputManager::GetInstance().AddInputComponent(this);

	for (std::pair<const InputOptions, std::vector<Command*>>& p : m_pCommands) for (Command* pC : p.second) pC->SetGameObject(GetGameObject());
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
		if (CheckKeyboard(static_cast<UINT8>(p.first.keyboard))) for (Command* pC : p.second)  pC->Execute();
	}
}
void InputComponent::Render() const
{
}
void InputComponent::CheckInput()
{
	if(m_pGamepad->IsConnected())UpdateGamepad();
	UpdateKeyboard();
}
void InputComponent::AddCommand(Command* pCommand, InputOptions button)
{
	if (AddCheck(m_pCommands[button], pCommand)) pCommand->SetGameObject(GetGameObject());
}
Gamepad* InputComponent::GetGamepad() const
{
	return m_pGamepad;
}
bool InputComponent::CheckKeyboard(UINT8 scan)
{
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);

	return pStates[static_cast<Uint8>(scan)];
}
