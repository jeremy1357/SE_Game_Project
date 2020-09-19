#include "GameScreen.h"

GameScreen::GameScreen(int uniqueScreenID)
{
	m_screenID = uniqueScreenID;
}

void GameScreen::init()
{
	// Add initialization code here for your objects
	// Ex) npcs.init();
	// ETC....

}

void GameScreen::onEntry()
{
	m_screenState = ScreenState::ACTIVE;

}

void GameScreen::onExit()
{
	m_screenState = ScreenState::INACTIVE;
}

void GameScreen::onRender()
{
	// Put code here for rendering
}

void GameScreen::onUpdate()
{
	// Put code here for updating
	// EX) updateParticleManager();

}
