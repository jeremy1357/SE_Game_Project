#include "MenuScreen.h"
#include "imgui.h"
#include "ScreenManager.hpp"

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
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	
	ImGui::Begin("Main Menu");
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 1.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	
	
	
	ImGui::Text("Zombies & Sprites");
	ImGui::ShowDemoWindow();

	//std::string text = "Zombie Killer";

	//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(text.c_str()).x - ImGui::GetScrollX() - 55 * ImGui::GetStyle().ItemSpacing.x);
	//ImGui::Text("%s", text);

	if (ImGui::Button("Play Game")) {
		m_screenManager->setScreen(ScreenKeys::GAME);
	}

	if (ImGui::Button("Top Scorers")) {
		//m_screenManager->setScreen(ScreenKeys::GAME);
	}

	if (ImGui::Button("Settings")) {
		m_screenManager->setScreen(ScreenKeys::SETTINGS);
	}

	if (ImGui::Button("Exit Game")) {
		m_screenManager->m_isProgramRunning = false;
	}

	ImGui::End();

}

void MenuScreen::on_update()
{

}
