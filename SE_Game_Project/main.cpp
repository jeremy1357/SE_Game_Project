

#include <iostream>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include "ScoringScreen.h"

#include "ScreenManager.hpp"
#include <glm/glm.hpp>


ScreenManager gameManager;




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
	std::unique_ptr<ScoringScreen> scoringScreen = nullptr;

	// We then create a unique ptr of GameScreen and call its
	// constructor with a numeric ID which will ONLY be associated
	// the game play screen. I made an enum to visualize this easier
	gameScreen = std::make_unique<GameScreen>(ScreenKeys::GAME);
	menuScreen = std::make_unique<MenuScreen>(ScreenKeys::MENU);
	settingsScreen = std::make_unique<SettingsScreen>(ScreenKeys::SETTINGS);
	scoringScreen = std::make_unique<ScoringScreen>(ScreenKeys::SCORES);

	// Now give our GameScreen object to the screen manager so it can manage it
	gameManager.addScreen(gameScreen.get(), false);
	gameManager.addScreen(menuScreen.get(), false);
	gameManager.addScreen(scoringScreen.get(), false);
	gameManager.addScreen(settingsScreen.get(), false);


	// This sets our current screen to the game play screen
	// In the future, change to main menu
	gameManager.setScreen(ScreenKeys::MENU);


	// Now give off control the manager to run everything else
	// Everyone only has to worry about implementing stuff in GameScreen
	// Dylan and Corey may need to add stuff to the ScreenManager
	gameManager.runProgram();


	return 0;
}