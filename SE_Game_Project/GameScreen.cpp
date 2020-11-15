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
	m_characterManager.m_zombieManager.set_zombie_sound_keys(m_screenManager->m_soundDelegate.get_key("zombie0.wav"), m_screenManager->m_soundDelegate.get_key("zombie9.wav"));

	m_characterManager.init(m_screenManager->m_inputManager, 
		m_levelManager, 
		m_collisionManager, 
		m_screenManager->m_camera,
		m_screenManager->m_soundDelegate,
		glm::vec2(900, 3075),
		m_screenManager->get_project_directory());

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

	for (auto& it : m_characterManager.m_zombieManager.m_zombies) {
		m_spriteRenderer.add_sprite_to_batch(it.position, glm::vec2(25.0f), "skeleton-idle_1.png", it.angle);
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

	ImGui::Begin("Zombie Onslaught");
	ImGui::Text("FPS: %f", m_screenManager->m_timer.m_fps);
	ImGui::Text("Health: %i", m_characterManager.m_player.health);
	ImGui::Text("Money: $%i", m_characterManager.m_player.money);
	// Added by Jeremy for debugging
	glm::vec2 worldCursorCoordinates = m_screenManager->m_camera.get_world_cursor_position();
	ImGui::Text("X: [%i]  Y: [%i]", (int)worldCursorCoordinates.x, (int)worldCursorCoordinates.y);
	ImGui::Text("[%c]", m_levelManager.get_character(worldCursorCoordinates, true));

	if (ImGui::Button("Main Menu")) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}
	//ImGui::Text("Zombie Wave: );
	ImGui::End();

	ImGui::Begin("Gun");
	ImGui::Text(("Gun: " + m_characterManager.get_gun_name()).c_str());
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
	
	m_characterManager.m_player.angle = m_screenManager->m_camera.playerCursorAngle;
	m_characterManager.update();

	

}
