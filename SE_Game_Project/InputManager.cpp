/*Dylan Beauchemin*/
/*September 29, 2020*/
#include <SDL/SDL.h>
#include <map>
#include "InputManager.h"



InputManager::InputManager() {
	//Constructor
	m_LeftMB = 0;
	m_RightMB = 0;
	m_MPosX = 0;
	m_MPosY = 0;

	//CurrentKeystate = SDL_GetKeyboardState(NULL);
}

InputManager::~InputManager() {

}

void InputManager::m_Update() {
	//SDL Events Loop - When no events, goes to 0
	//October 6, 2020
	while (SDL_PollEvent(&m_InputEvent)) {
		switch (m_InputEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
			m_SetMouseClick(m_InputEvent.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_UnMouseClick(m_InputEvent.button);
		case SDL_KEYDOWN:
			m_Keys[m_InputEvent.key.keysym.scancode] = true;
		case SDL_KEYUP:
			m_Keys[m_InputEvent.key.keysym.scancode] = false;
		default:
			break;
		}
	}
	//Mouse position updated at the addresses of MPos
	SDL_GetRelativeMouseState(&m_MPosX, &m_MPosY);
}

bool InputManager::m_GetKey(int Key){
	if (m_Keys[Key])
		return true;
	else
		return false;
}

void InputManager::m_SetMouseClick(SDL_MouseButtonEvent& Button) {
	//Checking both left and right buttons to ensure 
	if (Button.button == SDL_BUTTON_LEFT)
		m_LeftMB = 1;
	if (Button.button == SDL_BUTTON_RIGHT)
		m_RightMB = 1;
}

void InputManager::m_UnMouseClick(SDL_MouseButtonEvent& Button)
{
	if (Button.button == SDL_BUTTON_LEFT)
		m_LeftMB = 0;
	if (Button.button == SDL_BUTTON_RIGHT)
		m_RightMB = 0;
}
