#define IMGUI_DEFINE_MATH_OPERATORS
#include "MenuScreen.h"
#include "imgui.h"
#include "ScreenManager.hpp"
#include "imgui_internal.h"
#include "SDLWindow.h"


MenuScreen::MenuScreen(int uniqueScreenID)
{
	m_screenID = uniqueScreenID;

}

void MenuScreen::on_init()
{
}

void MenuScreen::on_entry()
{
	m_screenManager->m_soundDelegate.play_music(m_screenManager->m_soundDelegate.get_key("ZombiesAreComing.ogg"));
	m_screenState = ScreenState::ACTIVE;
}

void MenuScreen::on_exit()
{
	m_screenManager->m_soundDelegate.stop_music(m_screenManager->m_soundDelegate.get_key("ZombiesAreComing.ogg"));
	m_screenState = ScreenState::INACTIVE;
}

void MenuScreen::on_render()
{
	//Demo window for testing
	//ImGui::ShowDemoWindow();

	//Color Defines
	#define TEXT(v) ImVec4(0.999f, 0.100f, 0.100f, v) //Text color define
	#define BG(v)   ImVec4(0.100f, 0.100f, 0.100f, v) //Background color define

	//Getting Style
	ImGuiStyle& style = ImGui::GetStyle();

	//Setting Up Colors of different things
	style.Colors[ImGuiCol_Text] = TEXT(0.99f); //Changing color of text
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.100f, 0.100f, 0.100f, 0.100f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.100f, 0.100f, 0.100f, 0.100f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.100f, 0.100f, 0.100f, 0.100f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.900f, 0.900f, 0.900f, 0.900f);

	//Window Details
	int tempHeight = m_screenManager->m_window.get_height();
	int tempWidth = m_screenManager->m_window.get_width();
	int height = tempHeight / 2;
	int width = tempWidth / 2;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Zombie Onslaught");
	ImGui::SetWindowFontScale(1.5);
	style.WindowBorderSize = 1.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;
	

	float buttonPlayGameSize = 225.0f;
	ImGui::SameLine(width - 112.5);
	if (ImGui::Button("Play Game", ImVec2(buttonPlayGameSize, 50))) {
		m_screenManager->setScreen(ScreenKeys::GAME);
	}

	ImGui::NewLine();
	float buttonTopScorers = 250.0f;
	ImGui::SameLine(width - 125);
	if (ImGui::Button("Top Scorers", ImVec2(buttonTopScorers, 50))) {
		//m_screenManager->setScreen(ScreenKeys::GAME);
	}

	ImGui::NewLine();
	float buttonSettings = 200.0f;
	ImGui::SameLine(width - 100);
	if (ImGui::Button("Settings", ImVec2(buttonSettings, 50))) {
		m_screenManager->setScreen(ScreenKeys::SETTINGS);
	}

	ImGui::NewLine();
	float buttonExitGame = 200.0f;
	ImGui::SameLine(width - 100);
	if (ImGui::Button("Exit Game", ImVec2(buttonExitGame, 50))) {
		m_screenManager->m_isProgramRunning = false;
	}

	ImGui::End();

}

void MenuScreen::on_update()
{

}