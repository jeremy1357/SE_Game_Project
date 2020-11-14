#include "ZombieManager.h"
#include "LevelManager.h"
#include "CharacterManager.h"
#include <SDL/SDL.h>
#include<iostream>




ZombieManager::ZombieManager()
{

}

ZombieManager::~ZombieManager()
{

}

glm::vec2 ZombieManager::calculate_spawnPosition()
{
	glm::vec2 testPT = glm::vec2 (0.0);
	srand(time(0));

	for (int i = 0; i < 10; i++)
	{
		//testPT.x = rand() % m_mapSizex*m_tileSize.x;   //1 - 3899
		//testPT.y = rand() % m_mapSizey*m_tileSize.y;   //

		testPT.x = rand() % 3625 + 100;   //1 - 3899
		testPT.y = rand() % 7450 + 175;   //

		char result;
		result = m_levelManager->get_character(testPT, true);

		bool posCheck = collision_Check(result);

		if (posCheck == false)
		{
			break;
		}
	}
	return testPT;
	// 	int m_mapSizex;
	//	int m_mapSizey;
	//	glm::vec2 tileSize;



	//	for loop 10*max() if failed valid default value

	//	each time within the for loop, calculate a new random and x and y position
	//	verify that this position is valid by checking if it lands on a valid tile 



	//	use level manager get char -- pass in random position 
	//  function returns character at that position 

	//	then compare return char against blacklisted characters
	//	if no matches return position
}


void ZombieManager::init(LevelManager& levelManager, CharacterManager& characterManager, const std::vector<char> blacklistedTiles, int mapSizex, int mapSizey, glm::vec2 tileSize, CollisionManager& collisionManager)
{
	m_mapSizex = mapSizex;
	m_mapSizey = mapSizey;
	m_levelManager = &levelManager;
	m_characterManager = &characterManager;
	m_collisionManager = &collisionManager;
	m_blacklistedChar = blacklistedTiles;

}


void ZombieManager::spawn_Wave(int wave)
{
	m_zombies.clear();
	int numZombies = 10 * (wave)+10;

	for (int i = 0; i < numZombies; i++)
	{
		m_zombies.push_back(Zombie());
		m_zombies.back().position = calculate_spawnPosition();   //sets position to newest zombie using calcspawn function
	}
}



bool ZombieManager::collision_Check(char parameter)
{
	for (int i = 0; i < m_blacklistedChar.size(); i++) 
	{
		if (m_blacklistedChar[i] == parameter) 
		{
			return true;
		}
	}
	return false;
}

bool ZombieManager::should_spawn_wave()
{
	for (int i = 0; i < m_zombies.size(); i++)
	{
		if (m_zombies[i].isAlive)
		{
			return false;
		}
	}
	return true;
}


void ZombieManager::update()
{
	if (should_spawn_wave() == true)
	{
		spawn_Wave(wave++);
	}


	const float speed = 2.0f;
	float playerX = m_characterManager->m_player.position.x;
	float playerY = m_characterManager->m_player.position.y;

	//update the zombie position variables

	for (int i = 0; i < m_zombies.size(); i++)
	{
		//float angle = (atan2(playerY - m_zombies[i].position.y, playerX - m_zombies[i].position.x) * 180) / 3.141;
		float angle = (atan2(m_zombies[i].position.y - playerY, m_zombies[i].position.x - playerX) * 180) / 3.141;
		if (playerX > m_zombies[i].position.x)
		{
			m_zombies[i].position.x = m_zombies[i].position.x + speed;
			m_zombies[i].angle = angle;
		}

		if (playerY > m_zombies[i].position.y)
		{
			m_zombies[i].position.y = m_zombies[i].position.y + speed;
			m_zombies[i].angle = angle;
		}

		if (playerX < m_zombies[i].position.x)
		{
			m_zombies[i].position.x = m_zombies[i].position.x - speed;
			m_zombies[i].angle = angle;
		}

		if (playerY < m_zombies[i].position.y)
		{
			m_zombies[i].position.y = m_zombies[i].position.y - speed;
			m_zombies[i].angle = angle;
		}
	}
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

void ZombieManager::perform_tile_collision(CollisionPosition *cp) {
	for (int k = 0; k < m_zombies.size(); k++)
	{
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
void ZombieManager::npc_collision()
{

	float pushback = 5.0f;
	for (int i = 0; i < m_zombies.size(); i++)
	{
		for (int j = 0; j < m_zombies.size(); j++)
		{
			float dx = m_zombies[i].position.x-m_zombies[j].position.x;
			float dy = m_zombies[i].position.y - m_zombies[j].position.y;
			float radius = (dx * dx) + (dy * dy);
			if (radius < m_zombies[i].radius)
			{
				float angleZomb = (atan2(m_zombies[i].position.y - m_zombies[j].position.y, m_zombies[i].position.x - m_zombies[j].position.x) * 180) / 3.141;

				m_zombies[i].position.x = m_zombies[i].position.x + cos(angleZomb) * pushback;
				m_zombies[i].position.y = m_zombies[i].position.y + cos(angleZomb) * pushback;

				m_zombies[j].position.x = m_zombies[j].position.x - cos(angleZomb) * pushback;
				m_zombies[j].position.y = m_zombies[j].position.y - cos(angleZomb) * pushback;
			}
		}

	}
}