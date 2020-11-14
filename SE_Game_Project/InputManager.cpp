/*Dylan Beauchemin*/
/*September 29, 2020*/

#include <iostream>
#include "InputManager.h"

InputManager::InputManager() {
	// Constructor
	//m_leftMB = 0;
	//m_rightMB = 0;
	m_mPosX = 0;
	m_mPosY = 0;
	m_didPlayerCloseApp = false;
}

InputManager::~InputManager() {

}

void InputManager::update() {
	m_priorKeys = m_currentKeys;
	// SDL Events Loop - When no events, goes to 0
	// October 6, 2020
	while (SDL_PollEvent(&m_inputEvent)) {
		switch (m_inputEvent.type) {
			// using SDL keycodes
			// https://wiki.libsdl.org/SDL_Keycode
			// and mouse events
			// https://wiki.libsdl.org/SDL_MouseButtonEvent#Remarks
		case SDL_MOUSEBUTTONDOWN:
			m_currentKeys[m_inputEvent.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			m_currentKeys[m_inputEvent.button.button] = false;
			break;
		case SDL_KEYDOWN:
			m_currentKeys[m_inputEvent.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			m_currentKeys[m_inputEvent.key.keysym.sym] = false;
			break;
		case SDL_QUIT:
			m_didPlayerCloseApp = true;
			break;
		default:
			break;
		}
	}
	// Mouse position updated at the addresses of MPos
	SDL_GetMouseState(&m_mPosX, &m_mPosY);
}

bool InputManager::get_key(int key){
	// Inputs should be keycodes or mouse buttons
	if (m_currentKeys[key]) {
		return true;
	}
	else {
		return false;
	}
	// Checks keymap to see if keys are pressed
}

bool InputManager::get_if_closed() {
	return m_didPlayerCloseApp;
}

bool InputManager::get_keyHeld(int key) {
	if (m_priorKeys[key]) {
		return true;
	}
	else {
		return false;
	}
}

bool InputManager::get_keyPressed(int key) {
	if (m_priorKeys[key] == true && m_currentKeys[key] == false) {
		return true;
	}
	else {
		return false;
	}
}

/*void InputManager::set_mouse_click(SDL_MouseButtonEvent& button) {
	// Checking both left and right buttons
	if (button.button == SDL_BUTTON_LEFT)
		m_leftMB = 1;
	if (button.button == SDL_BUTTON_RIGHT)
		m_rightMB = 1;
}

void InputManager::un_mouse_click(SDL_MouseButtonEvent& button)
{
	if (button.button == SDL_BUTTON_LEFT) {
		m_leftMB = 0;
	}
	if (button.button == SDL_BUTTON_RIGHT) {
		m_rightMB = 0;
	}
}*/

