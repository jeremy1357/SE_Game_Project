// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include <SDL/SDL.h>

class SDLWindow
{
public:
	SDLWindow();
	~SDLWindow();
	int init(int width = 1024, int height = 768);
	void update();

private:
	int m_width = 0;
	int m_height = 0;
	float m_aspectRatio = 1.0f;
	SDL_Window* m_window = nullptr;
};