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
	A = 4,
	B, C, D, E, F, G, H, I, J, K, L, M,
	N, O, P, Q, R, S, T, U, V, W, X, Y, Z, 
	One, Two, Three, Four, Five, Six,
	Seven, Eight, Nine, Zero,
	Right = 79,
	Left, Down, Up,
	Enter = 40,
	Space = 44,
	One_KP = 89,
	Two_KP,Three_KP,Four_KP,Five_KP,
    Six_KP,Seven_KP,Eight_KP,Nine_KP,Zero_KP
};

struct InputOptions
{
	ControllerButton controller;
	KeyboardButton keyboard;
};
class Command;
class Gamepad;

class InputComponent final: public BaseComponent
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
	void AssignGamepad(int portNr = -1, bool forceAssign = true);//if true, will reassign an already assigned controller; Else no changes will be made if the controller is already assigned

private:
	std::map<InputOptions ,std::vector<Command*>> m_pCommands;
	Gamepad* m_pGamepad;

	bool CheckKeyboard(UINT8 scan);
	
	void UpdateGamepad();
	void UpdateKeyboard();

	friend class Gamepad;
	void UnbindGamepad();

	InputComponent(const InputComponent&) = delete;
	InputComponent(InputComponent&&) noexcept = delete;

	InputComponent& operator=(const InputComponent&) = delete;
	InputComponent& operator=(InputComponent&&) noexcept = delete;
};

