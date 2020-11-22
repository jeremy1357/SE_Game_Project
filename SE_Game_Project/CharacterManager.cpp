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

void CharacterManager::start_game(std::string name)
{
	// This function should reset the player if needed (dead)
	if (!m_player.isAlive) {
		bool shouldSearch = true;
		// Verify name isnt already stored
		while (shouldSearch) {
			for (int i = 0; i < m_scores.size(); i++) {
				if (name == m_scores[i].name) {
					name += "~";
				}
			}
			shouldSearch = false;
		}
		m_player.name		= name;
		m_player.angle		= 0.0f;
		m_player.isAlive	= true;
		m_player.money		= 500;
		m_player.position	= PLAYER_START_POINT;
		m_player.health		= 100;
		m_player.zombieKills = 0;
		m_inventory.clear();
		m_gameoverMusicPlaying = false;
		// TODO: Add in restart of particle manager
		// Add starting items
		add_item_to_inventory("Pistol");
		add_item_to_inventory("Shotgun");

		set_gun_index("Shotgun");
		m_zombieManager.reset();
		m_levelManager->reset_map_data();
	}
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

void CharacterManager::add_item_to_inventory(const std::string& itemName)
{
	Item item = m_economy.get_item(itemName);
	if (item.Name != "") {
		m_inventory.push_back(item);
	}
}

void CharacterManager::use_consumable_item(const std::string& itemName)
{
	for (size_t i = 0; i < m_inventory.size(); i++) {
		if (m_inventory[i].Name == itemName) {

		}
	}
}

void CharacterManager::attempt_to_buy_item(const std::string& itemName)
{
	for (auto& it : m_economy.itemList) {
		if (itemName == it.Name) {
			if (m_player.money >= it.Cost) {
				m_player.money -= it.Cost;
				m_inventory.push_back(m_economy.get_item(itemName));
			}
		}
	}
}

void CharacterManager::attempt_to_sell_item(const std::string& itemName)
{
	int index = 0;
	for (auto& it : m_inventory) {
		if (itemName == it.Name) {
			m_player.money += it.SellCost;
			m_inventory.erase(m_inventory.begin() + index);
			
		}
		index += 1;
	}
}

void CharacterManager::set_player_hurt_sound_ranges(int min, int max)
{
	m_characterSoundHurtMin = min;
	m_characterSoundHurtMax = max;
}

void CharacterManager::stop_game_over_music()
{
	m_soundDelegate->stop_effect(m_soundDelegate->get_key("GAMEOVER.wav"));
}

void CharacterManager::set_gun_index(const std::string& itemName)
{
	for (int i = 0; i < m_inventory.size(); i++) {
		if (m_inventory[i].Name == itemName && m_inventory[i].Type == 2) {
			m_currentGunIndex = i;
			return;
		}
	}
	m_currentGunIndex = -1;
}

std::string CharacterManager::get_gun_name()
{
	if (m_currentGunIndex != -1) {
		return m_inventory[m_currentGunIndex].Name;
	}
	return std::string();
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
	const std::string &programDirectory)
{
	m_inputManager		= &inputManager;
	m_levelManager		= &levelManager;
	m_collisionManager	= &collisionManager;
	m_camera			= &camera;
	m_soundDelegate		= &soundDelegate;
	blacklistedChar = m_levelManager->get_restricted_tiles();
	m_economy.init(programDirectory, 20);
	m_particleManager.particle_init(collisionManager);

	m_zombieManager.init(levelManager, *this, collisionManager, soundDelegate, m_particleManager);
}

void CharacterManager::update(float playerAngle)
{
	if (m_player.health <= 0 && m_player.isAlive)
	{
		m_player.isAlive = false;
		m_scores.push_back(Score(m_player.name, m_zombieManager.wave));
		if (m_gameoverMusicPlaying == false) {
			m_soundDelegate->play_effect(m_soundDelegate->get_key("GAMEOVER.wav"), -1);
			m_gameoverMusicPlaying = false;
		}
		
	}
	else if (m_player.isAlive)
	{
		m_zombieManager.update();
		m_particleManager.update_particle();
		m_player.angle = playerAngle;
		const float speed = 3.5f;
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
					m_soundDelegate->play_effect(2, 1);
					m_soundDelegate->play_effect(3);
				}
			}
		}
		if (m_inputManager->get_keyPressed(SDL_BUTTON_LEFT)) {
			if (m_inventory[m_currentGunIndex].bulletsPerShot != 1) {
				for (int i = 0; i < m_inventory[m_currentGunIndex].bulletsPerShot; i++) {
					glm::vec2 dirVector(cos(m_player.angle * 3.14157 / 180), sin(m_player.angle * 3.14157 / 180));
					glm::vec2 bulletPos = m_player.position + dirVector * 10.0f;
					m_particleManager.update_AddParticle(bulletPos, m_player.angle + rand() % 10 - 4, ColorRGBA32(0, 0, 0, 255));
				}
			}
			else {
				glm::vec2 dirVector(cos(m_player.angle * 3.14157 / 180), sin(m_player.angle * 3.14157 / 180));
				glm::vec2 bulletPos = m_player.position + dirVector * 10.0f;
				m_particleManager.update_AddParticle(bulletPos, m_player.angle, ColorRGBA32(0, 0, 0, 255));
			}
			m_soundDelegate->play_effect(0);


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

	collisionAreas[0].position.x -= m_spriteRadius;
	collisionAreas[0].position.y += m_spriteRadius;
	collisionAreas[2].position -= glm::vec2(m_spriteRadius);
	collisionAreas[1].position += glm::vec2(m_spriteRadius);
	collisionAreas[3].position.x += m_spriteRadius;
	collisionAreas[3].position.y -= m_spriteRadius;


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

