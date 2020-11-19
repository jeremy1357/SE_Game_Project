#include "ZombieManager.h"
#include "LevelManager.h"
#include "CharacterManager.h"
#include <SDL/SDL.h>
#include<iostream>
#include <random>




ZombieManager::ZombieManager()
{

}

ZombieManager::~ZombieManager()
{

}

glm::vec2 ZombieManager::calculate_spawnPosition()
{
	glm::vec2 testPT = glm::vec2 (0.0);
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> disX(100.0, 3725.0);
	std::uniform_real_distribution<> disY(175.0, 7625.0);

	for (int i = 0; i < 10; i++)
	{
		//testPT.x = rand() % m_mapSizex*m_tileSize.x;   //1 - 3899
		//testPT.y = rand() % m_mapSizey*m_tileSize.y;   //
		
		testPT.x = disX(gen);   
		
		testPT.y = disY(gen);   

		char result;
		result = m_levelManager->get_character(testPT, true);

		bool posCheck = collision_Check(result);

		if (posCheck == false)
		{
			break;
		}
	}
	return testPT;
}


void ZombieManager::init(LevelManager& levelManager, 
	CharacterManager& characterManager, 
	CollisionManager& collisionManager, 
	SoundDelegate& sound)
{
	m_levelManager		= &levelManager;
	m_characterManager	= &characterManager;
	m_collisionManager	= &collisionManager;
	soundDelegate		= &sound;
	m_mapSize			= levelManager.get_map_size();
	m_blacklistedChar	= levelManager.get_restricted_tiles();
	m_tileSize			= levelManager.get_tile_dimensions();
	minDistBetweenSprites = m_characterManager->get_sprite_radius() * 2.0f;

}


void ZombieManager::spawn_Wave(int wave)
{
	m_zombies.clear();
	int numZombies = 10 * (wave)+10;

	for (int i = 0; i < numZombies; i++) 	{
		m_zombies.push_back(Zombie());
		m_zombies.back().position = calculate_spawnPosition();   //sets position to newest zombie using calcspawn function
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<float> disX(1.0f, 4.0f);
		m_zombies.back().speed = disX(rd);
	}
}

void ZombieManager::collide_with_player(Zombie* zombie)
{
	// Get distance from center to center
	float dist_a_to_b = glm::length(m_characterManager->m_player.position - zombie->position);
	if (dist_a_to_b < minDistBetweenSprites) {
		glm::vec2 normalizedAngle = glm::normalize(m_characterManager->m_player.position - zombie->position);
		float collisionDepth = minDistBetweenSprites - dist_a_to_b;
		glm::vec2 push = normalizedAngle * collisionDepth;

		m_characterManager->m_player.position += push / 2.0f;
		zombie->position -= push / 2.0f;
	}

}

bool ZombieManager::collision_Check(char parameter)
{
	for (int i = 0; i < m_blacklistedChar.size(); i++) {
		if (m_blacklistedChar[i] == parameter) {
			return true;
		}
	}
	return false;
}

bool ZombieManager::should_spawn_wave()
{
	for (int i = 0; i < m_zombies.size(); i++) {
		if (m_zombies[i].isAlive) {
			return false;
		}
	}
	return true;
}


void ZombieManager::update() {
	if (should_spawn_wave() == true) {
		spawn_Wave(wave++);
	}
	// If false, zombies are still alive so play a sound (roll a dice)
	else {
		if (rand() % 400 < 3) {
			soundDelegate->play_effect(m_zombieSoundKeys[rand() % 10]);
		}
	}


	float playerX = m_characterManager->m_player.position.x;
	float playerY = m_characterManager->m_player.position.y;

	//update the zombie position variables
	for (auto& it : m_zombies) {
		float angleRads = atan2(it.position.y - playerY, it.position.x - playerX);
		float angleDegrees = angleRads * 180.0f / 3.14157f;
		it.position -= glm::vec2(cos(angleRads), sin(angleRads)) * it.speed;
		it.angle = angleDegrees;
	}



	// This is bad below, left in so you can see
	//for (int i = 0; i < m_zombies.size(); i++)
	//{
	//	const float speed = m_zombies[i].speed;

	//	float angle = ( * 180) / 3.141;

	//	if (playerX > m_zombies[i].position.x)
	//	{
	//		m_zombies[i].position.x = m_zombies[i].position.x + speed;
	//		m_zombies[i].angle = angle;
	//	}

	//	if (playerY > m_zombies[i].position.y)
	//	{
	//		m_zombies[i].position.y = m_zombies[i].position.y + speed;
	//		m_zombies[i].angle = angle;
	//	}

	//	if (playerX < m_zombies[i].position.x)
	//	{
	//		m_zombies[i].position.x = m_zombies[i].position.x - speed;
	//		m_zombies[i].angle = angle;
	//	}

	//	if (playerY < m_zombies[i].position.y)
	//	{
	//		m_zombies[i].position.y = m_zombies[i].position.y - speed;
	//		m_zombies[i].angle = angle;
	//	}
	//}
	 //Need to have zombie implement angle to face player


	for (int i = 0; i < m_zombies.size(); i++)
	{
		if (m_zombies[i].health < 0)
		{
			m_zombies[i].isAlive = false;
		}
		else
		{
			const float speed = 2.0f;
			m_zombies[i].isAlive = true;
			tile_collision();
		}
	}

	npc_collision();
}

void ZombieManager::tile_collision() {
	for (int i = 0; i < m_zombies.size(); i++)
	{
		glm::vec2 worldSize = m_levelManager->get_map_size();
		CollisionPosition collisionAreas[4];
		collisionAreas[0].position = m_zombies[i].position; //TL
		collisionAreas[1].position = m_zombies[i].position; //TR
		collisionAreas[2].position = m_zombies[i].position; //BL
		collisionAreas[3].position = m_zombies[i].position; //BR

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
			if (collision_Check(cornerCharacters[i])) {
				collisionAreas[i].didCollisionOccur = true;
			}
		}
		perform_tile_collision(collisionAreas);
	}
}

void ZombieManager::set_zombie_sound_keys(int min, int max) {
	for (int i = min; i <= max; i++) {
		m_zombieSoundKeys.push_back(i);
	}
}

void ZombieManager::perform_tile_collision(CollisionPosition *cp) {
	for (int k = 0; k < m_zombies.size(); k++) {
		for (int i = 0; i < 4; i++) {
			if (cp[i].didCollisionOccur) {
				glm::vec2 tileCenter = m_levelManager->get_tile_center(cp[i].position);
				glm::vec2 vectorFromTileToPlayer = m_zombies[k].position - tileCenter;
				const float radius = 25.0f;
				// 75 should not be a hard coded constant. CHANGE 
				const float distTillCollision = radius + (75.0f / 2); // 75.0f is the window of a tile.
				float x = distTillCollision - abs(vectorFromTileToPlayer.x);
				float y = distTillCollision - abs(vectorFromTileToPlayer.y);

				if (x > 0 && y > 0) {
					if (std::max(x, 0.0f) < std::max(y, 0.0f)) {
						if (vectorFromTileToPlayer.x < 0) {
							m_zombies[k].position.x -= x;
						}
						else {
							m_zombies[k].position.x += x;
						}
					}
					else {
						if (vectorFromTileToPlayer.y < 0) {
							m_zombies[k].position.y -= y;
						}
						else {
							m_zombies[k].position.y += y;
						}
					}
				}
			}
		}
	}
}

void ZombieManager::npc_collision() {
	// This logic is saying that zombie is colliding with zombie j
	for (int i = 0; i < m_zombies.size(); i++) {
		for (int j = 0; j < m_zombies.size(); j++) {
			if (i != j) {
				// Get distance from center to center
				float dist_a_to_b = glm::length(m_zombies[i].position - m_zombies[j].position);
				if (dist_a_to_b < minDistBetweenSprites) {
					glm::vec2 normalizedAngle = glm::normalize(m_zombies[i].position - m_zombies[j].position);
					float collisionDepth = minDistBetweenSprites - dist_a_to_b;
					glm::vec2 push = normalizedAngle * collisionDepth;
					m_zombies[i].position += push / 2.0f;
					m_zombies[j].position -= push / 2.0f;
				}
			}
		}
		collide_with_player(&m_zombies[i]);

	}
}

void ZombieManager::bullet_collision(Particle* particle) {
	for (int i = 0; i < m_zombies.size(); i++) {
		float dist_a_to_b = glm::length(m_zombies[i].position - particle->position);
		if (dist_a_to_b < minDistBetweenSprites) {
			float collisionDepth = minDistBetweenSprites - dist_a_to_b;
			m_zombies[i].health - 25;
		}
	}
}