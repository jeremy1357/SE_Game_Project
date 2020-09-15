#include <iostream>
#include "SDLWindow.h"
#include <glm/glm.hpp>

// To allow these includes to work you must specify the include and lib
// pathway. Already set so dont change
#include <SDL/SDL.h> 
#include <GL/glew.h>

int main(int argc, char** argv) {
	SDLWindow window;
	window.init();

	std::cout << "Start of game!\n";

	char a;
	std::cin >> a;

	return 0;
}