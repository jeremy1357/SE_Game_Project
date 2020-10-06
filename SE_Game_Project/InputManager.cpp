/*Dylan Beauchemin*/
/*September 29, 2020*/
#include <SDL/SDL.h>
#include "InputManager.h"



InputManager::InputManager() {
	//Constructor
	LeftMB = 0; RightMB = 0;
	WKey = 0; AKey = 0; SKey = 0; DKey = 0;
	MPosX = 0; MPosY = 0;;
}

InputManager::~InputManager() {

}

void InputManager::Update() {
	//SDL Events Loop - When no events, goes to 0
	//October 6, 2020
	while (SDL_PollEvent(&InputEvent)) {
		switch (InputEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
			SetMouseClick(InputEvent.button);
			break;
		case SDL_MOUSEBUTTONUP:
			UnMouseClick(InputEvent.button);
		case SDL_KEYDOWN:
			SetKeyboardState(InputEvent.key);
		case SDL_KEYUP:
			UnKeyboardState(InputEvent.key);
		default:
			break;
		}
	}
	//Mouse position updated at the addresses of MPos
	SDL_GetRelativeMouseState(&MPosX, &MPosY);
}

void InputManager::SetKeyboardState(SDL_KeyboardEvent& Keys) {
	//If I got this right, it should catch the scancodes of relevant keys and set the bool for retrieval
	//Scancodes are hardware and should work regardless of keyboard
	switch (Keys.keysym.scancode) {
	case SDL_SCANCODE_W:
		WKey = 1;
		break;
	case SDL_SCANCODE_A:
		AKey = 1;
		break;
	case SDL_SCANCODE_S:
		SKey = 1;
		break;
	case SDL_SCANCODE_D:
		DKey = 1;
		break;
	default:
		break;
	}
}

void InputManager::UnKeyboardState(SDL_KeyboardEvent& Keys)
{
	//Reverse of before
	switch (Keys.keysym.scancode) {
	case SDL_SCANCODE_W:
		WKey = 0;
		break;
	case SDL_SCANCODE_A:
		AKey = 0;
		break;
	case SDL_SCANCODE_S:
		SKey = 0;
		break;
	case SDL_SCANCODE_D:
		DKey = 0;
		break;
	default:
		break;
	}
}

void InputManager::SetMouseClick(SDL_MouseButtonEvent& Button) {
	//Checking both left and right buttons to ensure 
	if (Button.button == SDL_BUTTON_LEFT)
		LeftMB = 1;
	if (Button.button == SDL_BUTTON_RIGHT)
		RightMB = 1;
}

void InputManager::UnMouseClick(SDL_MouseButtonEvent& Button)
{
	if (Button.button == SDL_BUTTON_LEFT)
		LeftMB = 0;
	if (Button.button == SDL_BUTTON_RIGHT)
		RightMB = 0;
}
