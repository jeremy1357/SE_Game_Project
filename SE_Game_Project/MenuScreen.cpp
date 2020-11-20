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
	m_menuEffects.init(m_screenManager->get_project_directory());
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
	//Color Defines
    #define TEXT(v) ImVec4(0.900f, 0.100f, 0.100f, v)
	#define BG(v)   ImVec4(0.100f, 0.100f, 0.100f, v) //Background color define

	//Getting Style
	ImGuiStyle& style = ImGui::GetStyle();

	//Setting Up Colors of different things
	style.Colors[ImGuiCol_Text] = TEXT(0.99f); //Changing color of text
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.100f, 0.100f, 0.100f, 0.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.500f, 0.500f, 0.500f, 0.7f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.100f, 0.100f, 0.100f, 0.100f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.900f, 0.900f, 0.900f, 0.900f);

	//Window Details
	int tempHeight = m_screenManager->m_window.get_height();
	int tempWidth = m_screenManager->m_window.get_width();
	int height = tempHeight / 2;
	int width = tempWidth / 2;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImVec2 windowSize;
	windowSize.x = m_screenManager->m_window.get_width();
	windowSize.y = m_screenManager->m_window.get_height();
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin("Zombie Onslaught", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	style.WindowBorderSize = 1.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::NewLine();

	string inputText[300] = {};
	ImGui::InputText("Enter Player Username", inputText, sizeof(inputText));

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::NewLine();

	float buttonPlayGameSize = 225.0f;
	ImGui::SameLine(width - 112.5);
	if (ImGui::Button("Play Game", ImVec2(buttonPlayGameSize, 50))) {
		m_screenManager->setScreen(ScreenKeys::GAME);

	}
	
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::NewLine();

	float buttonTopScorers = 250.0f;
	ImGui::SameLine(width - 125);
	if (ImGui::Button("Top Scorers", ImVec2(buttonTopScorers, 50))) {
		m_screenManager->setScreen(ScreenKeys::SCORES);
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::NewLine();

	float buttonSettings = 200.0f;
	ImGui::SameLine(width - 100);
	if (ImGui::Button("Settings", ImVec2(buttonSettings, 50))) {
		m_screenManager->setScreen(ScreenKeys::SETTINGS);
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::NewLine();

	float buttonExitGame = 200.0f;
	ImGui::SameLine(width - 100);
	if (ImGui::Button("Exit Game", ImVec2(buttonExitGame, 50))) {
		m_screenManager->m_isProgramRunning = false;
	}
	ImGui::InputText("Enter Text", buf1, 64);

	ImGui::End();
	glm::vec2 cursorPosition(m_screenManager->m_inputManager.m_mPosX, m_screenManager->m_inputManager.m_mPosY);
	m_menuEffects.render(m_screenManager->m_camera, cursorPosition);

}

void MenuScreen::on_update()
{

}