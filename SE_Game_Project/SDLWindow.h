#pragma once
#include <SDL/SDL.h>

class SDLWindow
{
public:
	SDLWindow();
	~SDLWindow();
	void init(int width = 1024, int height = 768);

private:
	int m_width = 0;
	int m_height = 0;
	SDL_Window* m_window = nullptr;
};

