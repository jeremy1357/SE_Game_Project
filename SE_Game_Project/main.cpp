

#include <iostream>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"

#include "ScreenManager.hpp"
#include <glm/glm.hpp>


ScreenManager gameManager;

// As of right now, only screen is the gameplay screen
// In the future we may have a main menu, settings, etc...
// If we do, add the unique screen ID here,
// Example, SETTINGS = 1
enum ScreenKeys {
	GAME = 0,
	MENU = 1,
	SETTINGS = 2
};


int main(int argc, char** argv) 
{
	std::cout << "This is the start of game!\n";
	// Initialize screen manager
	gameManager.init();
	// We add different "screens" to the game here
	// These are SMART pointers. Handles some of the
	// downfalls of normal raw pointers. Less dangerous
	// The eventual deletion of these pointers are handled 
	// by the system. NOT US
	// LEARN THIS
	std::unique_ptr<GameScreen> gameScreen = nullptr;
	std::unique_ptr<MenuScreen> menuScreen = nullptr;
	std::unique_ptr<SettingsScreen> settingsScreen = nullptr;

	// We then create a unique ptr of GameScreen and call its
	// constructor with a numeric ID which will ONLY be associated
	// the game play screen. I made an enum to visualize this easier
	gameScreen = std::make_unique<GameScreen>(ScreenKeys::GAME);
	menuScreen = std::make_unique<MenuScreen>(ScreenKeys::MENU);
	settingsScreen = std::make_unique<SettingsScreen>(ScreenKeys::SETTINGS);

	// Now give our GameScreen object to the screen manager so it can manage it
	gameManager.addScreen(gameScreen.get(), false);
	gameManager.addScreen(menuScreen.get(), false);
	gameManager.addScreen(settingsScreen.get(), false);


	// This sets our current screen to the game play screen
	// In the future, change to main menu
	gameManager.setScreen(ScreenKeys::GAME);


	// Now give off control the manager to run everything else
	// Everyone only has to worry about implementing stuff in GameScreen
	// Dylan and Corey may need to add stuff to the ScreenManager
	gameManager.runProgram();


	// This is a dirty way to stop the terminal from closing automatically
	// after we click exit on the game. Useful for seeing any prints to the
	// terminal before shutdown
	// Bascially a hold statement
	char a;
	std::cin >> a;

	return 0;
}