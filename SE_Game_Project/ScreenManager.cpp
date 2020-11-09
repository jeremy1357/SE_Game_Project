#include "ScreenManager.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include <windows.h>

void ScreenManager::runProgram()
{
	this->enable();
	while (m_isProgramRunning) {
		// FPS Timer START would go HERE
		m_timer.start_FPS();
		update();
		render();
		m_timer.end_FPS();

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
			it->second->on_init();
		}
	}

}

void ScreenManager::setScreen(int screenID) {
	// Call the current screens onExit function to do any specific 
	// requirements it may have
	if (m_currentScreen != nullptr) {
		m_currentScreen->on_exit();
	}

	// Find the new screen based off the ID passed in
	std::unordered_map<int, Screen*>::const_iterator it = m_screens.find(screenID);
	if (it != m_screens.end()) {
		if (it->second->m_screenState == ScreenState::NONE) {
			it->second->on_init();
		}
		it->second->on_entry();
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
	m_inputManager.update();
	// Verify that the currentScreen points to a valid memory address
	// If so, call that screens update function to perform specific update functionality
	// Ex) Can call the game play screen which updates NPCs
	// ETC....
	for (auto& it : m_screens) {
		switch (it.second->m_screenState) {
		case ScreenState::ACTIVE:
			it.second->on_update();
			break;
		case ScreenState::BACKGROUND:
			it.second->on_update();
		default:
			break;
		}
	}
}

void ScreenManager::render()
{
	// This stuff must be done every render. Ignore
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window.get_window_handle());
	ImGui::NewFrame();
		
	// Verify that the currentScreen points to a valid memory address
	// If so, call that screens update function to perform specific update functionality
	// Ex) Can call the gameplay render function which renders NPCs
	// ETC....
	if (m_currentScreen != nullptr) {
		m_currentScreen->on_render();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("A:/Downloads/04b_30/04B_30__.TTF", 16.0f);

	m_window.update();

}

// ADD ANY INITIALIZATION CODE TO THIS FUNCTION
void ScreenManager::init()
{
	// KEEP THIS. This is a common source where we can easily get the
	// project directory.
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	m_projectDirectory = std::string(buf) + '\\';
	std::cout << "Project directory: " << m_projectDirectory << std::endl;


	// Create our window with default resolution
	int error = m_window.init();
	if (error != 0) {
		disable();
		return;
	}

	// Call any other crucial initialization code here
	// Screen specific things should be initialized in their specific init functions

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(m_window.get_window_handle(), m_window.glContext);
	ImGui_ImplOpenGL3_Init("#version 130");

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\Windows\Fonts\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);
	m_soundDelegate.init_sound_delegate(m_projectDirectory);
	m_soundDelegate.load_WAV("shotgun.wav");
	m_camera.set_scale(1.2);
	m_camera.init_camera(m_window.get_width(), m_window.get_height());
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
