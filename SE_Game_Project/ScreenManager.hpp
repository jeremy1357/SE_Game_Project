// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include "Screen.hpp"
#include "SDLWindow.h"
#include <unordered_map>
#include <GL/glew.h>

class Screen;

class ScreenManager
{
public:
	void runProgram();
	void addScreen(Screen* screen, bool shouldInitializeScreen);
	void setScreen(int screenID);
	void update();
	// This calls the main rendering functions and the
	// screens rendering function
	void render();
	void init();
	void destroy();
	void enable();
	void disable();

	//Screen* getCurrentScreen();
	SDLWindow m_window;

protected:
	Screen* m_currentScreen = nullptr;
	std::unordered_map<int, Screen*> m_screens;
	bool m_isProgramRunning = false;
	// TODO: Add the input manager

};

