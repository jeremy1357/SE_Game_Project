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

	ImGui::Begin("Settings");
	if (ImGui::Button("Main Menu")) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}

	ImGui::SliderInt("FPS", &m_maxFPS, 60, 90);
	m_screenManager->m_timer.max_FPS = std::chrono::duration<float>(m_maxFPS);
	ImGui::SliderFloat("Camera Scale", &m_screenManager->m_camera.m_scale, 0.5, 2.0);

	ImGui::End();
}

void SettingsScreen::on_update()
{
}
