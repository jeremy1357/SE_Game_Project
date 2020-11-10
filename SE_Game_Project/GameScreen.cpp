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
	m_characterManager.init(m_screenManager->m_inputManager, m_levelManager, glm::vec2(900, 3075));
	m_economy.init(m_screenManager->get_project_directory());
}

void GameScreen::on_entry()
{
	m_screenState = ScreenState::ACTIVE;
}

void GameScreen::on_exit()
{
	m_screenState = ScreenState::INACTIVE;
}

void GameScreen::on_render()
{
	m_levelManager.render(glm::vec2(0.0, 0.0), glm::vec2(0.0f));
	m_spriteRenderer.add_sprite_to_batch(m_characterManager.m_player.position, glm::vec2(25.0f), "player.png", m_screenManager->m_camera.playerCursorAngle);
	m_spriteRenderer.add_light_to_batch(glm::vec2(810.0f, 3040.0f), glm::vec2(100.0f), ColorRGBA32(255, 180, 255, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(1100.0f, 4040.0f), glm::vec2(200.0f), ColorRGBA32(255, 255, 255, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(1742.0f, 3180.0f), glm::vec2(170.0f), ColorRGBA32(123, 0, 0, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(840.0f, 2130.0f), glm::vec2(150.0f), ColorRGBA32(95, 95, 95, 255));
	m_spriteRenderer.add_light_to_batch(glm::vec2(1470.0f, 5500.0f), glm::vec2(350.0f), ColorRGBA32(0, 0, 180, 255));

	m_spriteRenderer.on_render();
	
	ImGui::SetNextWindowBgAlpha(0.35f);

	ImGui::Begin("Zombie Onslaught");
	ImGui::Text("FPS: %f", m_screenManager->m_timer.m_fps);
	ImGui::Text("Player Health: %i", m_characterManager.m_player.health);
	ImGui::Text("Player Money: %i", m_characterManager.m_player.money);
	// Added by Jeremy for debugging
	glm::vec2 worldCursorCoordinates = m_screenManager->m_camera.get_world_cursor_position();
	ImGui::Text("CURSOR: X: [%i]  Y: [%i]", (int)worldCursorCoordinates.x, (int)worldCursorCoordinates.y);
	ImGui::Text("PLAYER: X: [%i]  Y: [%i]", (int)m_characterManager.m_player.position.x, (int)m_characterManager.m_player.position.y);
	ImGui::Text("Character Hover: X: [%c]", m_levelManager.get_character(worldCursorCoordinates, true));

	if (ImGui::Button("Main Menu")) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}
	//ImGui::Text("Zombie Wave: );
	ImGui::End();
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
	m_characterManager.update();


	if (m_screenManager->m_inputManager.get_key(SDLK_q)) {
		std::cout << "Mouse X: " << m_screenManager->m_inputManager.m_mPosX << std::endl;
		std::cout << "Mouse Y: " << m_screenManager->m_inputManager.m_mPosY << std::endl;
		std::cout << "FPS: " << m_screenManager->m_timer.m_fps << std::endl;
		m_screenManager->m_soundDelegate.play_effect(0);
	}
	

}
