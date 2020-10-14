#pragma once
/*Dylan Beauchemin*/
/*September 29, 2020*/
#include <SDL/SDL.h>
#include <map>

class InputManager{
public:
	bool m_LeftMB, m_RightMB;
	int m_MPosX, m_MPosY;
	InputManager();
	~InputManager();
	void m_Update();
	bool m_GetKey(int Key);
private:
	SDL_Event m_InputEvent;
	std::map<int, bool> m_Keys;
	//const Uint8* CurrentKeystate;
	void m_SetMouseClick(SDL_MouseButtonEvent& Button);
	void m_UnMouseClick(SDL_MouseButtonEvent& Button);
};

