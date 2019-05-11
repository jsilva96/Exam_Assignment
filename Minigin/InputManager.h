#pragma once
#include "Singleton.h"

class InputComponent;
class InputManager final : public dae::Singleton<InputManager>
{
public:
	bool ProcessInput();

	void AddInputComponent(InputComponent* pComponent);
	Point2f GetMousePos() const;
private:

	std::vector<InputComponent*> m_Comps;
	Point2f m_MousePos;
};
