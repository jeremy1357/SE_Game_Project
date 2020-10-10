#include "ScreenManager.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

void ScreenManager::runProgram()
{
	this->enable();
	this->init();

	while (m_isProgramRunning) {
		// FPS Timer START would go HERE

		update();
		render();

		// FPS Timer END would go HERE

	}
	std::cout << "Exited main control loop. Shutting down.\n";
	this->destroy();
}

void ScreenManager::addScreen(Screen* screen, bool shouldInitializeScreen)
{
	std::unordered_map<int, Screen*>::const_iterator it = m_screens.find(screen->m_screenID);

	// Only add the new screen if the ID is not already present
	if (it == m_screens.end()) {
		m_screens.insert(std::pair<int, Screen*>(screen->m_screenID, screen));
		// Update the iterator with the new screen element
		it = m_screens.find(screen->m_screenID);

		// Set that screens screenManager pointer to this screenManagers address
		it->second->m_screenManager = this;

		// Initialize the screen if wanted
		if (shouldInitializeScreen && it->second->m_screenState == ScreenState::NONE) {
			it->second->init();
		}
	}

}

void ScreenManager::setScreen(int screenID)
{
	// Call the current screens onExit function to do any specific 
	// requirements it may have
	if (m_currentScreen != nullptr) {
		m_currentScreen->onExit();
	}

	// Find the new screen based off the ID passed in
	std::unordered_map<int, Screen*>::const_iterator it = m_screens.find(screenID);
	if (it != m_screens.end()) {
		if (it->second->m_screenState == ScreenState::NONE) {
			it->second->init();
		}
		it->second->onEntry();
		m_currentScreen = it->second;
	}
	else {
		std::cout << "Failed trying to set a new screen. ID not found in map.";
	}

}

void ScreenManager::update()
{
	// We would call any update functions that need to happen across
	// the entire game here.
	// Ex) The input manager update function should be called here
	// Since every screen depends on it

	// Verify that the currentScreen points to a valid memory address
	// If so, call that screens update function to perform specific update functionality
	// Ex) Can call the gameplay screen which updates NPCs
	// ETC....
	for (auto& it : m_screens) {
		switch (it.second->m_screenState) {
		case ScreenState::ACTIVE:
			it.second->onUpdate();
			break;
		case ScreenState::BACKGROUND:
			it.second->onUpdate();
		default:
			break;
		}
	}
}

void ScreenManager::render()
{
	// This stuff must be done every render. Ignore
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();
		
	// Verify that the currentScreen points to a valid memory address
	// If so, call that screens update function to perform specific update functionality
	// Ex) Can call the gameplay render function which renders NPCs
	// ETC....
	if (m_currentScreen != nullptr) {
		m_currentScreen->onRender();
	}

	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_window.update();

}

// ADD ANY INITIALIZATION CODE TO THIS FUNCTION
void ScreenManager::init()
{
	// Create our window with default resolution
	int error = m_window.init();
	if (error != 0) {
		disable();
		return;
	}

	// Call any other crucial initialization code here
	// Screen specific things should be initialized in their specific init functions

}

void ScreenManager::destroy()
{
	// Add code here for shutdown
	// EX) Calling a function to delete things declared with new
}

void ScreenManager::enable()
{
	m_isProgramRunning = true;
}

void ScreenManager::disable()
{
	m_isProgramRunning = false;

}
