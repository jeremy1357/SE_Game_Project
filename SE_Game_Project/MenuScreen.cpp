#include "MenuScreen.h"
#include "imgui.h"

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
	ImGui::Begin("Main Menu");
	ImGui::Button("Play Game");
	ImGui::Button("Top Scorers");
	ImGui::Button("Settings");
	ImGui::Button("Exit Game");
	ImGui::End();

}

void MenuScreen::on_update()
{

}
