#pragma once
/*Dylan Beauchemin*/
/*September 29, 2020*/

#include <SDL/SDL.h>
#include <map>
#include "FPS_Timer.h"

class InputManager{
public:
	//bool m_leftMB; //Depreciated; use map instead
	//bool m_rightMB;
	int m_mPosX;
	int m_mPosY;
	InputManager();
	~InputManager();
	void update();
	bool get_key(int key);
	bool get_if_closed();
	bool get_keyHeld(int key);
	bool get_keyPressed(int key);
private:
	SDL_Event m_inputEvent;
	std::map<int, bool> m_currentKeys;
	std::map<int, bool> m_priorKeys;
	bool m_didPlayerCloseApp;
	//void set_mouse_click(SDL_MouseButtonEvent& button); //Depreciated; use map instead
	//void un_mouse_click(SDL_MouseButtonEvent& button);
};

