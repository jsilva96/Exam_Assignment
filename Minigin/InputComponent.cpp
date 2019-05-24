#include "MiniginPCH.h"
#include "InputComponent.h"
#include "Command.h"
#include "InputManager.h"
#include "Gamepad.h"
#include "PoolManager.h"

bool operator<(InputOptions obj1, InputOptions obj2) { return obj1.controller < obj2.controller; };

InputComponent::InputComponent()
	:m_pGamepad{InputManager::GetInstance().GetGamepad()}
{
}
InputComponent::~InputComponent()
{
	for (std::pair<const InputOptions, std::vector<Command*>>& p : m_pCommands)
	{
		for (Command* pC : p.second) DeleteCheck(pC);
	}
//	DeleteCheck(m_pGamepad);

	m_pCommands.clear();
}
void* InputComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<InputComponent>();
}
void InputComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<InputComponent>(ptrDelete);
}
void InputComponent::Initialize()
{
	if (m_pGamepad)
	{
		m_pGamepad->AssignInput(this);
		m_pGamepad->CheckController();
	}
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
		if (m_pGamepad->IsPressed(static_cast<WORD>(p.first.controller))) for (Command* pC : p.second)
		{
			pC->Execute();
			GetGameObject()->OnNotify(pC->GetEvent());
		}
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

void InputComponent::AssignGamepad(int portNr, bool forceAssign)
{
	m_pGamepad = InputManager::GetInstance().GetGamepad(portNr, forceAssign);

	if(m_pGamepad)
	{
		if (!m_pGamepad->IsConnected()) throw std::runtime_error("Connecting to non-existent gamepad\n");
		
		if (m_pGamepad->IsAssigned() && forceAssign) m_pGamepad->UnbindInput();
		m_pGamepad->AssignInput(this);

	}
}

void InputComponent::UnbindGamepad()
{
	m_pGamepad = nullptr;
}
bool InputComponent::CheckKeyboard(UINT8 scan)
{
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);

	return pStates[static_cast<Uint8>(scan)];
}
