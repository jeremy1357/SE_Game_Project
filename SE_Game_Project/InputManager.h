#pragma once
/*Dylan Beauchemin*/
/*September 29, 2020*/
#include <SDL/SDL.h>

class InputManager
{
public:
	bool LeftMB, RightMB, WKey, AKey, SKey, DKey;
	int MPosX, MPosY;
	InputManager();
	~InputManager();
	void Update();
private:
	SDL_Event InputEvent;
	void SetKeyboardState(SDL_KeyboardEvent& Keys);
	void UnKeyboardState(SDL_KeyboardEvent& Keys);
	void SetMouseClick(SDL_MouseButtonEvent& Button);
	void UnMouseClick(SDL_MouseButtonEvent& Button);
};

