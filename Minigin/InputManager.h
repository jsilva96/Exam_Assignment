#pragma once
#include "Singleton.h"

class InputComponent;
class Gamepad;
class InputManager final : public dae::Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

	bool ProcessInput();

	void AddInputComponent(InputComponent* pComponent);
	Point2f GetMousePos() const;

	Gamepad* GetGamepad(int portNr = -1 , bool forceAssign = false);
private:
	static const int m_MaxNrOfGamepads = 4;
	Gamepad* m_pGamepads[m_MaxNrOfGamepads];

	std::vector<InputComponent*> m_Comps;
	Point2f m_MousePos;
};
