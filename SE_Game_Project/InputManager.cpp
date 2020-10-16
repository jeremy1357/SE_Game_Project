/*Dylan Beauchemin*/
/*September 29, 2020*/

#include "InputManager.h"

InputManager::InputManager() {
	// Constructor
	m_leftMB = 0;
	m_rightMB = 0;
	m_mPosX = 0;
	m_mPosY = 0;

	//CurrentKeystate = SDL_GetKeyboardState(NULL); //ignore this
}

InputManager::~InputManager() {

}

void InputManager::update() {

	// SDL Events Loop - When no events, goes to 0
	// October 6, 2020
	while (SDL_PollEvent(&m_inputEvent)) {
		switch (m_inputEvent.type) {
			// using SDL keycodes
			// https://wiki.libsdl.org/SDL_Keycode
		case SDL_MOUSEBUTTONDOWN:
			set_mouse_click(m_inputEvent.button);
			break;
		case SDL_MOUSEBUTTONUP:
			un_mouse_click(m_inputEvent.button);
			break;
		case SDL_KEYDOWN:
			m_keys[m_inputEvent.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			m_keys[m_inputEvent.key.keysym.sym] = false;
			break;
		default:
			break;
		}
	}
	// Mouse position updated at the addresses of MPos
	SDL_GetMouseState(&m_mPosX, &m_mPosY);
}

bool InputManager::get_key(int key){
	// Inputs should be keycodes
	if (m_keys[key])
		return true;
	else
		return false;
	// Checks keymap to see if keys are pressed
}

void InputManager::set_mouse_click(SDL_MouseButtonEvent& button) {
	// Checking both left and right buttons
	if (button.button == SDL_BUTTON_LEFT)
		m_leftMB = 1;
	if (button.button == SDL_BUTTON_RIGHT)
		m_rightMB = 1;
}

void InputManager::un_mouse_click(SDL_MouseButtonEvent& button)
{
	if (button.button == SDL_BUTTON_LEFT)
		m_leftMB = 0;
	if (button.button == SDL_BUTTON_RIGHT)
		m_rightMB = 0;
}
