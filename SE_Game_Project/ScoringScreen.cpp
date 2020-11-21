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

	//ImGui::Text("Top Scorer: ")
	for (auto& it : m_characterManager.m_scores.itemList) {
		ImGui::Columns(4, "mixed");
		ImGui::Text(it.Name.c_str());
		ImGui::NextColumn();
		ImGui::Text("%i", it.Cost);
		ImGui::SameLine(50.0f);
		if (ImGui::Button(("Buy##" + it.Name).c_str())) {
			m_characterManager.attempt_to_buy_item(it.Name);

		}
		ImGui::NextColumn();
		ImGui::Text("%i", it.SellCost);
		ImGui::SameLine(50.0f);
		if (ImGui::Button(("Sell##" + it.Name).c_str())) {
			m_characterManager.attempt_to_sell_item(it.Name);
		}
		ImGui::NextColumn();
		switch (it.Type) {
		case 0:
			ImGui::Text("Armor");
			ImGui::Text("Dmg % Block %i", it.Armor);
			break;
		case 1:
			ImGui::Text("Consumable");
			ImGui::Text("Health Regen %i", it.healthRegen);
			break;
		case 2:
			ImGui::Text("Weapon");
			ImGui::Text("Damage %i", it.damage);
			ImGui::Text("Bullets per shot %i", it.bulletsPerShot);
			break;
		}
		ImGui::Columns(1);
		ImGui::Separator();
	}


	ImGui::End();
}

void ScoringScreen::on_update()
{
}
