#include "SDLWindow.h"

SDLWindow::SDLWindow()
{
}

SDLWindow::~SDLWindow()
{
}

void SDLWindow::init(int width, int height)
{
	m_window = SDL_CreateWindow("Software Engineering Project", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	m_height = height;
	m_width = width;
}
