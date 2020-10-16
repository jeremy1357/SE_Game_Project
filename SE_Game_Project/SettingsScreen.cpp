#include "SettingsScreen.h"
#include "imgui.h"

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
	// ImGui code here
	// Probably need to create member variables
	static int sliderInt = 0;

	if (ImGui::Button("Main Menu")) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}

	ImGui::SliderInt("FPS", &sliderInt, 30, 500);

}

void SettingsScreen::on_update()
{
}
