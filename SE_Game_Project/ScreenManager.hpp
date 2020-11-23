// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include "Screen.hpp"
#include "SDLWindow.h"
#include "FPS_Timer.h"
#include "InputManager.h"
#include "Camera.h"
#include "SoundDelegate.h"
#include "Score.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include <unordered_map>
#include <GL/glew.h>
#include <string.h>

#define TEXT(v) ImVec4(0.0f, 0.0f, 0.0f, v) //Text color define


// As of right now, only screen is the gameplay screen
// In the future we may have a main menu, settings, etc...
// If we do, add the unique screen ID here,
// Example, SETTINGS = 1
enum ScreenKeys {
	GAME = 0,
	MENU = 1,
	SETTINGS = 2,
	SCORES = 3
};

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

	std::string get_project_directory() const { return m_projectDirectory; }

	SDLWindow m_window;
	FPS_Timer m_timer;
	InputManager m_inputManager;
	Camera m_camera;
	SoundDelegate m_soundDelegate;
	std::string m_playerName = "Steve";
	std::unordered_map<int, Screen*> m_screens;
	std::vector<Score> m_scores;
	ImFont* m_bigFont;
	ImFont* m_smallFont;
	ImFont* m_megaFont;

	bool m_isProgramRunning = false;
protected:
	std::string m_projectDirectory = "";
	Screen* m_currentScreen = nullptr;
	
	// TODO: Add the input manager
};

