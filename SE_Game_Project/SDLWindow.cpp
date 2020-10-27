#include "SDLWindow.h"
#include <iostream>
#include <GL/glew.h>

enum WindowError {
	SDL_WINDOW_FAILURE = 1,
	SDL_GLCONTEXT_FAILURE = 2,
	GLEW_INIT_FAILURE = 3
};

SDLWindow::SDLWindow()
{
}

SDLWindow::~SDLWindow()
{
}

int SDLWindow::init(int width, int height)
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	m_windowHandle = SDL_CreateWindow("Software Engineering Project", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	// Check if window was created successfully. If not return 1
	if (m_windowHandle == nullptr) {
		std::cout << "Failed to create SDL window. Error = " << SDL_GetError() << std::endl;
		return SDL_WINDOW_FAILURE;
	}
	else {
		std::cout << "SDL window created successfully." << std::endl;
	}

	glContext = SDL_GL_CreateContext(m_windowHandle);
	if (glContext == nullptr) {
		std::cout << "Failed to create SDL_GLContext. Error = " << SDL_GetError() << std::endl;
		return SDL_GLCONTEXT_FAILURE;
	}
	else {
		std::cout << "SDL_GLContext created successfully." << std::endl;
	}

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "Failed to initialize GLEW. Error = " << glewError << std::endl;
		return GLEW_INIT_FAILURE;
	}
	else {
		std::cout << "GLEW initiated successfully." << std::endl;
	}

	m_height = height;
	m_width = width;
	m_aspectRatio = (float)m_width / (float)m_height;
	glViewport(0, 0, m_width, m_height);

	// Set VSync to off
	SDL_GL_SetSwapInterval(1);
	glEnable(GL_MULTISAMPLE);

	// Enable transparency 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	std::cout << "SDL and OpenGL initiated." << std::endl;

	return 0;
}

void SDLWindow::update()
{
	int tempX, tempY;
	SDL_GetWindowSize(m_windowHandle, &tempX, &tempY);

	// If this is true, the window was resized
	if (m_height != tempY || m_width != tempX) {
		m_width = tempX;
		m_height = tempY;
		glViewport(0, 0, m_width, m_height);

		// Update the aspect ratio with the new window dimensions
		m_aspectRatio = (float)m_width / (float)m_height;
	}
	SDL_GL_SwapWindow(m_windowHandle);

}
