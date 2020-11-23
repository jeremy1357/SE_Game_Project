#include "GameScreen.h"
#include "imgui.h"
#include <string>

GameScreen::GameScreen(int uniqueScreenID)
{
	m_screenID = uniqueScreenID;
}

void GameScreen::on_init()
{
	m_spriteRenderer.on_init(m_screenManager->m_camera, m_textureCache, m_screenManager->get_project_directory());
	m_levelManager.init(m_screenManager->get_project_directory(), m_spriteRenderer, m_textureCache);

	m_collisionManager.init(m_levelManager);

	// This must be at the end
	// Set this before the init function
	m_characterManager.m_zombieManager.set_zombie_sound_keys(m_screenManager->m_soundDelegate.get_key("zombie0.wav"), 
					m_screenManager->m_soundDelegate.get_key("zombie9.wav"));
	m_characterManager.set_player_hurt_sound_ranges(m_screenManager->m_soundDelegate.get_key("aargh0.ogg"),
					m_screenManager->m_soundDelegate.get_key("aargh7.ogg"));
	
	m_characterManager.init(m_screenManager->m_inputManager, 
		m_levelManager, 
		m_collisionManager, 
		m_screenManager->m_camera,
		m_screenManager->m_soundDelegate,
		m_screenManager->get_project_directory(),
		m_screenManager->m_scores);

}

void GameScreen::on_entry()
{
	m_screenState = ScreenState::ACTIVE;
	m_characterManager.start_game(m_screenManager->m_playerName);
}

void GameScreen::on_exit()
{
	m_characterManager.stop_game_over_music();
	m_screenState = ScreenState::INACTIVE;
}

void GameScreen::on_render()
{
	m_levelManager.render(glm::vec2(0.0, 0.0), glm::vec2(0.0f));

	for (auto& it : m_characterManager.m_zombieManager.m_zombies) {
		if (it.isAlive) {
			m_spriteRenderer.add_sprite_to_batch(it.position, glm::vec2(25.0f), "skeleton-idle_1.png", it.angle);
		}
	}
	
	m_spriteRenderer.add_sprite_to_batch(m_characterManager.m_player.position, 
		glm::vec2(25.0f), "player.png", m_characterManager.m_player.angle);
	m_spriteRenderer.add_light_to_batch(glm::vec2(810.0f, 3040.0f), glm::vec2(100.0f), ColorRGBA32(255, 180, 255, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(1100.0f, 4040.0f), glm::vec2(200.0f), ColorRGBA32(255, 255, 255, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(1742.0f, 3180.0f), glm::vec2(170.0f), ColorRGBA32(123, 0, 0, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(840.0f, 2130.0f), glm::vec2(150.0f), ColorRGBA32(95, 95, 95, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(1470.0f, 5500.0f), glm::vec2(350.0f), ColorRGBA32(0, 0, 180, 255));
	for (auto& it : m_characterManager.m_particleManager.m_particles) {
		if (it.isActive) {
			m_spriteRenderer.add_particle_to_batch(it.position, it.size, it.m_color);
		}
	}
	m_spriteRenderer.on_render();
	render_inventory();
	render_shop();
	render_widget1();
	render_widget2();
	if (!m_characterManager.m_player.isAlive) {
		
		int tempHeight = m_screenManager->m_window.get_height();
		int tempWidth = m_screenManager->m_window.get_width();
		int height = tempHeight / 2;
		int width = tempWidth / 2;
		ImGui::SetNextWindowPos(ImVec2(width - 300, height));
		ImGui::SetNextWindowSize(ImVec2(550, 100));
		ImGui::Begin("DEATH", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowFontScale(3.0f);
		ImGui::Text("YOU ARE DEAD!");
		ImGui::SetWindowFontScale(1.0f);

		ImGui::End();
	}
}

void GameScreen::on_update()
{
	m_spriteRenderer.on_update();
	glm::vec2 cursorPos(
		m_screenManager->m_inputManager.m_mPosX, 
		m_screenManager->m_inputManager.m_mPosY);

	m_screenManager->m_camera.update_camera(
		m_characterManager.m_player.position, 
		cursorPos, 
		m_screenManager->m_window.get_width(),
		m_screenManager->m_window.get_height());
	
	m_characterManager.update(m_screenManager->m_camera.playerCursorAngle, ImGui::IsWindowHovered(ImGuiFocusedFlags_AnyWindow));

}

void GameScreen::render_shop()
{
	int tempWidth = m_screenManager->m_window.get_width();
	int width = tempWidth / 4 + 300;
	ImGui::SetNextWindowPos(ImVec2(width, 0));
	ImGui::SetNextWindowSize(ImVec2(430, 300));
	int id = 0;
	ImGui::Begin("Shop", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushFont(m_screenManager->m_smallFont);
	ImGui::Columns(4, "mixed");
	ImGui::Separator();
	ImGui::Text("Name");
	ImGui::NextColumn();
	ImGui::Text("Buy Price");
	ImGui::NextColumn();
	ImGui::Text("Sell Price");
	ImGui::NextColumn();
	ImGui::Text("Item Type");
	ImGui::NextColumn();
	ImGui::Columns(1);
	ImGui::Separator();
	for (auto& it : m_characterManager.m_economy.itemList) {
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
			ImGui::Text("Dmg % Block: %i", it.Armor);
			break;
		case 1:
			ImGui::Text("Consumable");
			ImGui::Text("Health+: %i", it.healthRegen);
			break;
		case 2:
			ImGui::Text("Weapon");
			ImGui::Text("Damage: %i", it.damage);
			ImGui::Text("Bullets: %i", it.bulletsPerShot);
			break;
		}
		ImGui::Columns(1);
		ImGui::Separator();
	}
	ImGui::PopFont();
	ImGui::End();
}

void GameScreen::render_inventory()
{
	int tempWidth = m_screenManager->m_window.get_width();
	int width = tempWidth / 4.2;
	ImGui::SetNextWindowPos(ImVec2(width, 0));
	ImGui::SetNextWindowSize(ImVec2(300, 300));
	int id = 0;
	ImGui::Begin("Inventory", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushFont(m_screenManager->m_smallFont);
	ImGui::Columns(3, "mixed");
	ImGui::Separator();
	ImGui::Text("Name");
	ImGui::NextColumn();
	ImGui::Text("Attributes");
	ImGui::NextColumn();
	ImGui::Text("Action");
	ImGui::NextColumn();
	ImGui::Columns(1);
	ImGui::Separator();
	for (auto& it : m_characterManager.m_inventory) {
		ImGui::Columns(3, "mixed");
		ImGui::Text(it.Name.c_str());
		//ImGui::SetColumnWidth(1, 50.0f);
		ImGui::NextColumn();
		switch (it.Type) {
		case 0:
			ImGui::Text("Armor");
			ImGui::Text("Dmg % Block: %i", it.Armor);
			break;
		case 1:
			ImGui::Text("Consumable");
			ImGui::Text("Health +: %i", it.healthRegen);
			break;
		case 2:
			ImGui::Text("Weapon");
			ImGui::Text("Damage: %i", it.damage);
			ImGui::Text("Bullets: %i", it.bulletsPerShot);
			break;
		}
		//ImGui::SetColumnWidth(2, 50.0f);

		ImGui::NextColumn();
		switch (it.Type) {
		case 1:
			if (ImGui::Button(("Use##" + std::to_string(id)).c_str())) {
				m_characterManager.use_consumable(it.Name);
			}
			break;
		case 0:
			if (it.isEquipped) {
				if (ImGui::Button(("Unequip##" + std::to_string(id)).c_str())) {
					m_characterManager.toggleEquippableItem(it.Name);
				}
			}
			else {
				if (ImGui::Button(("Equip##" + std::to_string(id)).c_str())) {
					m_characterManager.toggleEquippableItem(it.Name);
				}
			}
			break;
		case 2:
			if (it.isEquipped) {
				ImGui::Text("Current gun");
			}
			else {
				if (ImGui::Button(("Equip##" + std::to_string(id)).c_str())) {
					m_characterManager.toggleEquippableItem(it.Name);
				}
			}

			break;
		}
		//ImGui::SetColumnWidth(3, 50.0f);

		ImGui::Columns(1);
		ImGui::Separator();
		id++;
	}
	ImGui::PopFont();
	ImGui::End();
}

void GameScreen::render_widget1()
{
	//int tempHeight = m_screenManager->m_window.get_height();
	//int tempWidth = m_screenManager->m_window.get_width();
	//int height = tempHeight / 2;
	//int width = tempWidth / 2;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(170, 190));
	ImGui::Begin("Zombie Onslaught", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text("FPS: %i", (int)m_screenManager->m_timer.m_fps);
	ImGui::Text("Health: %i", (int)m_characterManager.m_player.health);
	ImGui::Text("Money: $%i", m_characterManager.m_player.money);
	ImGui::Text("Armor: %i", m_characterManager.m_player.armor);
	ImGui::Text("Wave: %i", m_characterManager.m_zombieManager.wave);

	if (ImGui::Button("Main Menu")) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}
	ImGui::End();
}

void GameScreen::render_widget2()
{
	ImVec2 windowSize;
	windowSize.y = m_screenManager->m_window.get_height();
	ImGui::SetNextWindowPos(ImVec2(0, windowSize.y - 35));
	ImGui::SetNextWindowSize(ImVec2(170, 40));
	ImGui::Begin("Gun", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text(("Gun: " + m_characterManager.get_gun_name()).c_str());
	ImGui::End();
}
