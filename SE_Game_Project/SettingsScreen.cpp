#include "SettingsScreen.h"
#include "imgui.h"
#include <chrono>

SettingsScreen::SettingsScreen(int uniqueScreenID)
{
	m_screenID = uniqueScreenID;
}

void SettingsScreen::on_init()
{
}

void SettingsScreen::on_entry()
{
}

void SettingsScreen::on_exit()
{
}

void SettingsScreen::on_render()
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
	// ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders) | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	float mainMenuButtonSize = 200.0f;
	ImGui::SameLine(width - 100);
	if (ImGui::Button("Main Menu", ImVec2(mainMenuButtonSize, 50))) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::SliderInt("FPS", &m_maxFPS, 60, 90);
	m_screenManager->m_timer.max_FPS = std::chrono::duration<float>(m_maxFPS);
	
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	
	ImGui::SliderFloat("Camera Scale", &m_screenManager->m_camera.m_scale, 0.5, 2.0);

	ImGui::End();
}

void SettingsScreen::on_update()
{
}
