#pragma once
#include "BaseComponent.h"
#include <Xinput.h>
#include <map>

enum class ControllerButton
{
	ButtonA = XINPUT_GAMEPAD_A,
	ButtonB = XINPUT_GAMEPAD_B,
	ButtonX = XINPUT_GAMEPAD_X,
	ButtonY = XINPUT_GAMEPAD_Y,

	DPad_Left = XINPUT_GAMEPAD_DPAD_LEFT,
	DPad_Right = XINPUT_GAMEPAD_DPAD_RIGHT,
	DPad_Up = XINPUT_GAMEPAD_DPAD_UP,
	DPad_Down = XINPUT_GAMEPAD_DPAD_DOWN,

	LeftTrigger_Up = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RightTrigger_Up = XINPUT_GAMEPAD_RIGHT_SHOULDER,

	LeftThumbstick = XINPUT_GAMEPAD_LEFT_THUMB,
	RightThumbstick = XINPUT_GAMEPAD_RIGHT_THUMB,

	StartButton = XINPUT_GAMEPAD_START,
	SelectButton = XINPUT_GAMEPAD_BACK,
};
enum class KeyboardButton : UINT8
{
	Right = 79,
	Left = 80,
	Down = 81,
	Up = 82,
};

struct InputOptions
{
	ControllerButton controller;
	KeyboardButton keyboard;
};
class Command;
class Gamepad;

class InputComponent : public BaseComponent
{
public:
	InputComponent();
	virtual ~InputComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void CheckInput();

	void AddCommand(Command* pCommand, InputOptions button);

	Gamepad* GetGamepad() const;
private:
	std::map<InputOptions ,std::vector<Command*>> m_pCommands;
	Gamepad* m_pGamepad;

	bool CheckKeyboard(UINT8 scan);
	
	void UpdateGamepad();
	void UpdateKeyboard();

	InputComponent(const InputComponent&) = delete;
	InputComponent(InputComponent&&) noexcept = delete;

	InputComponent& operator=(const InputComponent&) = delete;
	InputComponent& operator=(InputComponent&&) noexcept = delete;
};

