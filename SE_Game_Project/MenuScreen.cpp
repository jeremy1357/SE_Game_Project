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
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.100f, 0.100f, 0.100f, 0.100f);

	//Window Details
	int tempHeight = m_screenManager->m_window.get_height();
	int tempWidth = m_screenManager->m_window.get_width();
	int height = tempHeight / 2;
	int width = tempWidth / 2;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Zombie Onslaught");
	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF(m_sc, 16.0f);
	ImGui::SetWindowFontScale(1.5);
	style.WindowBorderSize = 1.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;
	

	ImGui::SameLine(width);
	if (ImGui::Button("Play Game")) {
		m_screenManager->setScreen(ScreenKeys::GAME);
	}

	ImGui::NewLine();
	ImGui::SameLine(width);
	if (ImGui::Button("Top Scorers")) {
		//m_screenManager->setScreen(ScreenKeys::GAME);
	}

	ImGui::NewLine();
	ImGui::SameLine(width);
	if (ImGui::Button("Settings")) {
		m_screenManager->setScreen(ScreenKeys::SETTINGS);
	}

	ImGui::NewLine();
	ImGui::SameLine(width);
	if (ImGui::Button("Exit Game")) {
		m_screenManager->m_isProgramRunning = false;
	}

	ImGui::End();

}

void MenuScreen::on_update()
{

}
