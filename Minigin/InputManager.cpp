#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "InputComponent.h"
#include "Gamepad.h"

InputManager::InputManager()
{
	for(int i = 0; i < m_MaxNrOfGamepads; ++i)
	{
		m_pGamepads[i] = new Gamepad(i);
		m_pGamepads[i]->CheckController();
	}


}

InputManager::~InputManager()
{
}

bool InputManager::ProcessInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) return false;
	}

	m_MousePos.x = float(e.motion.x);
	m_MousePos.y = float(e.motion.y);

	for (InputComponent* pC : m_Comps)
	{
		pC->CheckInput();
	}

	return true;
}

void InputManager::AddInputComponent(InputComponent * pComponent)
{
	AddCheck<InputComponent*>(m_Comps, pComponent);
}

Point2f InputManager::GetMousePos() const
{
	return m_MousePos;
}
Gamepad* InputManager::GetGamepad(int portNr, bool forceAssign)
{
	if (portNr >= m_MaxNrOfGamepads || portNr < -1)
	{
		throw std::runtime_error("Searching for inexistent port\n");
	}
	if (portNr == -1 && forceAssign)
	{
		GetGamepad(0, forceAssign);
	}
	const auto startIt = std::begin(m_pGamepads);
	const auto endIt = std::end(m_pGamepads);

	const auto searchUnassigned = [](Gamepad* pG) {return !pG->IsAssigned(); };
	const auto searchPortNr = [portNr, forceAssign](Gamepad* pG)
	{
		if (pG->GetPortNr() != portNr) return false;
		else if (!pG->IsAssigned()) return true;

		return forceAssign;
	};


	auto it = (portNr == -1 && !forceAssign) ? std::find_if(startIt, endIt, searchUnassigned)
		                                     : std::find_if(startIt, endIt, searchPortNr);

	return (it == endIt) ? nullptr : (*it);
}
