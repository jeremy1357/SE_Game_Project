#define IMGUI_DEFINE_MATH_OPERATORS
#include "MenuScreen.h"
#include "imgui.h"
#include "ScreenManager.hpp"
#include "imgui_internal.h"

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
	ImGui::ShowDemoWindow();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Zombies & Sprites");
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 1.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;

	ImGui::SameLine(210);
	if (ImGui::Button("Play Game")) {
		m_screenManager->setScreen(ScreenKeys::GAME);
	}

	ImGui::NewLine();
	ImGui::SameLine(210);
	if (ImGui::Button("Top Scorers")) {
		//m_screenManager->setScreen(ScreenKeys::GAME);
	}

	ImGui::NewLine();
	ImGui::SameLine(210);
	if (ImGui::Button("Settings")) {
		m_screenManager->setScreen(ScreenKeys::SETTINGS);
	}

	ImGui::NewLine();
	ImGui::SameLine(210);
	if (ImGui::Button("Exit Game")) {
		m_screenManager->m_isProgramRunning = false;
	}

	ImGui::End();

}

void MenuScreen::on_update()
{

}
