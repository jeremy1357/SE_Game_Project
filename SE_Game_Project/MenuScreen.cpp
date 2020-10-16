#include "MenuScreen.h"

MenuScreen::MenuScreen(int uniqueScreenID)
{
	m_screenID = uniqueScreenID;

}

void MenuScreen::on_init()
{
}

void MenuScreen::on_entry()
{
	m_screenState = ScreenState::ACTIVE;
}

void MenuScreen::on_exit()
{
	m_screenState = ScreenState::INACTIVE;
}

void MenuScreen::on_render()
{
	// ImGui code here
	// Probably need to create member variables

}

void MenuScreen::on_update()
{

}
