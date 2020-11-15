#include "CharacterManager.h"
#include "CharacterManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include <SDL/SDL.h>
#include<iostream>


CharacterManager::CharacterManager()
{
	this->m_player.health = 100;
}


CharacterManager::~CharacterManager()
{

}

int CharacterManager::GetHealth()
{
	return this->m_player.health;
}

void CharacterManager::Damage(int amount)
{
	this->m_player.health -= amount;
}

string CharacterManager::GetName()
{
	return this->m_player.name;
}

void CharacterManager::SetName(string name)
{
	this->m_player.name = name;
}

bool CharacterManager::is_player_alive()
{
	return m_player.isAlive;
}

bool CharacterManager::collisionCheck(char parameter)
{
	for (int i = 0; i < blacklistedChar.size(); i++) {
		if (blacklistedChar[i] == parameter) {
			return true;
		}
	}
	return false;
}

void CharacterManager::init(
	InputManager& inputManager, 
	LevelManager& levelManager, 
	CollisionManager& collisionManager,
	Camera& camera,
	SoundDelegate& soundDelegate,
	const glm::vec2& playerPos,
	const std::string &programDirectory)
{
	m_inputManager		= &inputManager;
	m_levelManager		= &levelManager;
	m_collisionManager	= &collisionManager;
	m_camera			= &camera;
	m_player.position = playerPos;
	m_soundDelegate = &soundDelegate;


	blacklistedChar = m_levelManager->get_restricted_tiles();
	m_zombieManager.init(levelManager, *this, blacklistedChar, m_levelManager->get_map_size().x, m_levelManager->get_map_size().y, m_levelManager->get_tile_dimensions(), collisionManager);
	m_economy.init(programDirectory, 20);
	m_particleManager.particle_init(collisionManager);
}

void CharacterManager::update()
{
	m_zombieManager.update();
	if (m_player.health < 0)
	{
		m_player.isAlive = false;
	}
	else
	{
		const float speed = 4.0f;
		m_player.isAlive = true;
		if (m_inputManager->get_key(SDLK_w)) {
			m_player.position.y += speed;
		}
		if (m_inputManager->get_key(SDLK_s)) {
			m_player.position.y -= speed;
		}
		if (m_inputManager->get_key(SDLK_a)) {
			m_player.position.x -= speed;	
		}
		if (m_inputManager->get_key(SDLK_d)) {
			m_player.position.x += speed;
		}
		if (m_inputManager->get_keyPressed(SDLK_r)) {
			// Unlocking a door costs $200
			if (m_economy.Insufficient_Funds(m_player.money, 200)) {
				if (m_levelManager->unlock_tile(m_camera->get_world_cursor_position())) {
					m_player.money -= 200;
						std::cout << "UNLOCKED DOOR\n";
						m_soundDelegate->play_effect(2);
				}
			}
		}
		if (m_inputManager->get_keyPressed(SDL_BUTTON_LEFT)) {
			m_particleManager.update_AddParticle(glm::vec3(m_player.position, 0.0f), glm::vec3(m_player.direction, 0.0f), ColorRGBA32(255, 0, 0, 255));
		}
		tile_collision();
	}
}

void CharacterManager::tile_collision() {


	glm::vec2 worldSize = m_levelManager->get_map_size();
	CollisionPosition collisionAreas[4];
	collisionAreas[0].position = m_player.position; //TL
	collisionAreas[1].position = m_player.position; //TR
	collisionAreas[2].position = m_player.position; //BL
	collisionAreas[3].position = m_player.position; //BR

	collisionAreas[0].position.x -= dim.x;
	collisionAreas[0].position.y += dim.y;
	collisionAreas[2].position -= dim;
	collisionAreas[1].position += dim;
	collisionAreas[3].position.x += dim.x;
	collisionAreas[3].position.y -= dim.y;


	char cornerCharacters[4];
	cornerCharacters[0] = m_levelManager->get_character(collisionAreas[0].position, true);
	cornerCharacters[1] = m_levelManager->get_character(collisionAreas[1].position, true);
	cornerCharacters[2] = m_levelManager->get_character(collisionAreas[2].position, true);
	cornerCharacters[3] = m_levelManager->get_character(collisionAreas[3].position, true);

	for (int i = 0; i < 4; i++) {
		if (collisionCheck(cornerCharacters[i])) {
			collisionAreas[i].didCollisionOccur = true;
		}
	}
	perform_tile_collision(collisionAreas);
}

void CharacterManager::perform_tile_collision(CollisionPosition *cp) {
	for (int i = 0; i < 4; i++) {
		if (cp[i].didCollisionOccur) {
			glm::vec2 tileCenter = m_levelManager->get_tile_center(cp[i].position);
			glm::vec2 vectorFromTileToPlayer = m_player.position - tileCenter;
			const float radius = 25.0f;
			// 75 should not be a hard coded constant. CHANGE 
			const float distTillCollision = radius + (75.0f / 2); // 75.0f is the window of a tile.
			float x = distTillCollision - abs(vectorFromTileToPlayer.x);
			float y = distTillCollision - abs(vectorFromTileToPlayer.y);

			if (x > 0 && y > 0) {
				if (std::max(x, 0.0f) < std::max(y, 0.0f)) {
					if (vectorFromTileToPlayer.x < 0) {
						m_player.position.x -= x;
					}
					else {
						m_player.position.x += x;
					}
				}
				else {
					if (vectorFromTileToPlayer.y < 0) {
						m_player.position.y -= y;
					}
					else {
						m_player.position.y += y;
					}
				}
			}
		}
	}
}

