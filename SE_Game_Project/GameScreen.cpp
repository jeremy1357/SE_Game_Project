#include "GameScreen.h"
#include "imgui.h"


GameScreen::GameScreen(int uniqueScreenID)
{
	m_screenID = uniqueScreenID;
}

void GameScreen::on_init()
{
	// Add initialization code here for your objects
	// Ex) npcs.init();
	// ETC....
	m_camera.set_scale(1.0);
	m_camera.init_camera(m_screenManager->m_window.get_width(), m_screenManager->m_window.get_height());
	m_spriteRenderer.on_init(m_camera, m_textureCache, m_screenManager->get_project_directory());
	m_levelManager.init(m_screenManager->get_project_directory(), m_spriteRenderer, m_textureCache);
	
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
	//m_spriteRenderer.add_sprite_to_batch(glm::vec2(0.0f), glm::vec2(25.0f), "grass.PNG", 45.0f);
	//m_spriteRenderer.add_sprite_to_batch(glm::vec2(200.0f), glm::vec2(25.0f), "grass.PNG", 75.0f);
	//m_spriteRenderer.add_sprite_to_batch(glm::vec2(-100.0f), glm::vec2(25.0f), "Ground_01.PNG", 15.0f);
	m_spriteRenderer.add_static_sprite_to_batch(glm::vec2(-2, 2), m_levelManager.get_texture_ID('#'));
	m_spriteRenderer.add_static_sprite_to_batch(glm::vec2(-4, 2), m_levelManager.get_texture_ID('-'));


	m_spriteRenderer.add_sprite_to_batch(glm::vec2(-50.0f), glm::vec2(25.0f), "Ground_01.PNG", 0.0f);
	m_spriteRenderer.add_sprite_to_batch(glm::vec2(100.0f), glm::vec2(30.0f), "Dirt_01.png", 45.0f);
	//m_levelManager.render(glm::vec2(0.0, 0.0), glm::vec2(0.0f));
	m_spriteRenderer.add_sprite_to_batch(glm::vec2(0.0f), glm::vec2(25.0f), "player.png", 45.0f);
	m_spriteRenderer.on_render();
	
	ImGui::SetNextWindowBgAlpha(0.35f);
	
	
	if (ImGui::Button("Main Menu")) {
		m_screenManager->setScreen(ScreenKeys::MENU);
	}

	ImGui::Text("FPS: %fp", m_screenManager->m_timer.m_fps);
	ImGui::Text("Player Health: %i", m_characterManager.m_Player.health);
	ImGui::Text("Player Money: %i", m_characterManager.m_Player.money);
	//ImGui::Text("Zombie Wave: );


}

void GameScreen::on_update()
{
	// Put code here for updating
	// EX) updateParticleManager();

	m_spriteRenderer.on_update();
	m_camera.update_camera(glm::vec2(0.0f, 0.0f));

	if (m_screenManager->m_inputManager.get_key(SDLK_w)) {
		std::cout << "Mouse X: " << m_screenManager->m_inputManager.m_mPosX << std::endl;
		std::cout << "Mouse Y: " << m_screenManager->m_inputManager.m_mPosY << std::endl;
		std::cout << "FPS: " << m_screenManager->m_timer.m_fps << std::endl;
	}
	

}
