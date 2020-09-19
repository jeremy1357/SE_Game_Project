// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include "SDLWindow.h"
#include "ScreenManager.hpp"

enum class ScreenState {
	BACKGROUND,
	ACTIVE,
	NONE,
	INACTIVE
};


class ScreenManager;

class Screen
{
	friend class ScreenManager;
public:
	virtual void init()     = 0;
	virtual void onEntry()  = 0;
	virtual void onExit()   = 0;
	virtual void onRender() = 0;
	virtual void onUpdate() = 0;

	// This stores the pointer to the screen manager managing
	// this screen object. Useful if we need to access a 
	// screen manager variable within a screen
	ScreenManager* m_screenManager = nullptr;
	ScreenState m_screenState = ScreenState::NONE;
	int m_screenID;
};

