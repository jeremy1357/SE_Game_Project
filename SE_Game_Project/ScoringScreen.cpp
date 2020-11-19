#include "ScoringScreen.h"
#include "MenuScreen.h"
#include "imgui.h"
#include "ScreenManager.hpp"
#include "imgui_internal.h"
#include "SDLWindow.h"

ScoringScreen::ScoringScreen(int uniqueScreenID)
{
	m_screenID = uniqueScreenID;
}

void ScoringScreen::on_init()
{
}

void ScoringScreen::on_entry()
{
}

void ScoringScreen::on_exit()
{
}

void ScoringScreen::on_render()
{
	int tempHeight = m_screenManager->m_window.get_height();
	int tempWidth = m_screenManager->m_window.get_width();
	int height = tempHeight / 2;
	int width = tempWidth / 2;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImVec2 windowSize;
	windowSize.x = m_screenManager->m_window.get_width();
	windowSize.y = m_screenManager->m_window.get_height();
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin("Top Scorers", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	float buttonMainMenuSize = 200.0f;
	ImGui::SameLine(width - 100);
	if (ImGui::Button("Main Menu", ImVec2(buttonMainMenuSize, 50))) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}

	//ImGui::Text("First Place: ")
	//ImGui::Text("Second Place: ")
	//ImGui::Text("Third Place: ")

	ImGui::End();
}

void ScoringScreen::on_update()
{
}
