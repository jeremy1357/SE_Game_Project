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
	m_camera.init_camera(m_screenManager->m_window.get_width(), m_screenManager->m_window.get_height());
	m_spriteRenderer.on_init(m_camera);
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
	m_spriteRenderer.on_render(glm::vec2(0.0, 0.0));
	// Put code here for rendering
}

void GameScreen::on_update()
{
	// Put code here for updating
	// EX) updateParticleManager();
	m_spriteRenderer.on_update();
	m_camera.update_camera(glm::vec2(0.0, 0.0));


}
