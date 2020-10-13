#include "GameScreen.h"


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
	m_spriteRenderer.on_init(m_camera, m_textureCache);
	
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
	m_spriteRenderer.add_sprite_to_batch(glm::vec2(0.0f), glm::vec2(25.0f), "grass.PNG", 45.0f);
	m_spriteRenderer.add_sprite_to_batch(glm::vec2(200.0f), glm::vec2(25.0f), "grass.PNG", 75.0f);
	m_spriteRenderer.add_sprite_to_batch(glm::vec2(-100.0f), glm::vec2(25.0f), "dark_crate_five.PNG", 15.0f);
	m_spriteRenderer.add_sprite_to_batch(glm::vec2(-100.0f), glm::vec2(25.0f), "dark_crate_five.PNG", 0.0f);
	m_spriteRenderer.add_sprite_to_batch(glm::vec2(-400.0f), glm::vec2(25.0f, 30.0f), "dark_crate_five.PNG", 45.0f);

	m_spriteRenderer.on_render();
	// Put code here for rendering
}

void GameScreen::on_update()
{
	// Put code here for updating
	// EX) updateParticleManager();

	m_spriteRenderer.on_update();
	m_camera.update_camera(glm::vec2(0, 0));


}
