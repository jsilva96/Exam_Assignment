#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "InputComponent.h"

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
