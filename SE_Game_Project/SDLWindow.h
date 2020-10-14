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
	int get_width() { return m_width; }
	int get_height() { return m_height; }
	SDL_Window* get_window_handle() { return m_windowHandle; }
	SDL_GLContext glContext;

private:
	SDL_Window* m_windowHandle = nullptr;

	int m_width = 0;
	int m_height = 0;
	float m_aspectRatio = 1.0f;
};