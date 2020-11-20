#include "GameScreen.h"
#include "imgui.h"


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
		m_screenManager->get_project_directory());

}

void GameScreen::on_entry()
{
	m_screenState = ScreenState::ACTIVE;
	m_characterManager.start_game(m_screenManager->m_playerName);
}

void GameScreen::on_exit()
{
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
	
	ImGui::SetNextWindowBgAlpha(0.35f);

	int tempHeight = m_screenManager->m_window.get_height();
	int tempWidth = m_screenManager->m_window.get_width();
	int height = tempHeight / 2;
	int width = tempWidth / 2;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(230, 200));

	ImGui::Begin("Zombie Onslaught", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text("FPS: %i", (int)m_screenManager->m_timer.m_fps);
	ImGui::Text("Health: %i", m_characterManager.m_player.health);
	ImGui::Text("Money: $%i", m_characterManager.m_player.money);
	ImGui::Text("Wave: %i", m_characterManager.m_zombieManager.wave);
	//glm::vec2 worldCursorCoordinates = m_screenManager->m_camera.get_world_cursor_position();


	if (ImGui::Button("Main Menu")) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}
	//ImGui::Text("Zombie Wave: );
	ImGui::End();
	
	ImVec2 windowSize;
	windowSize.y = m_screenManager->m_window.get_height();
	ImGui::SetNextWindowPos(ImVec2(0, windowSize.y - 50));
	ImGui::SetNextWindowSize(ImVec2(250, 50));
	ImGui::Begin("Gun", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text(("Gun: " + m_characterManager.get_gun_name()).c_str());
	ImGui::End();

	render_game_screen();
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
	
	m_characterManager.update(m_screenManager->m_camera.playerCursorAngle);

}

void GameScreen::render_game_screen()
{
	//ImGui::ShowDemoWindow();
	//ImGui::SetNextWindowWidth(200);
	//ImGui::SetNextWindowSize(ImVec2(200, 300));
	ImGui::Begin("Shop");
	ImGui::SetWindowFontScale(0.70);
	for (auto& it : m_characterManager.m_economy.itemList) {
		ImGui::TextColored(ImVec4(0, 0, 0, 1), it.Name.c_str());
		ImGui::SameLine(120.0f);
		ImGui::TextColored(ImVec4(0, 0, 0, 1), "Cost: $%i", it.Cost);
		ImGui::SameLine(30.0f);
		if (ImGui::Button("BUY")) {
			// TODO: Logic with character manager her
		}
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0, 0, 0, 1), "Sell: $%i", it.SellCost);
		ImGui::SameLine(30.0f);
		if (ImGui::Button("SELL")) {
			// TODO: Logic with character manager her
		}

		// Render stuff specific to an item
		switch (it.Type) {
		case 0:

			break;
		case 1:

			break;

		case 2:

			break;

		}

		ImGui::Spacing();

	}
	ImGui::End();
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = TEXT(0.99f); //Changing color of text

}
