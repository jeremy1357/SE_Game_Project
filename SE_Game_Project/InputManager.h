#pragma once
/*Dylan Beauchemin*/
/*September 29, 2020*/

#include <SDL/SDL.h>
#include <map>

class InputManager{
public:
	bool m_leftMB, m_rightMB;
	int m_mPosX, m_mPosY;
	InputManager();
	~InputManager();
	void update();
	bool get_key(int key);
private:
	SDL_Event m_inputEvent;

	std::map<int, bool> m_keys;
	//const Uint8* CurrentKeystate;
	void set_mouse_click(SDL_MouseButtonEvent& button);
	void un_mouse_click(SDL_MouseButtonEvent& button);
};

