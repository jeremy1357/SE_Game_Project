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
	glm::vec2 playerP = m_characterManager->m_player.position;
	glm::vec2 tpMin = playerP - glm::vec2(1000.0f);
	glm::vec2 tpMax = playerP + glm::vec2(1000.0f);

	if (tpMin.x < 0.0f) {
		tpMin.x = 0.0f;
	}
	if (tpMin.y < 0.0f) {
		tpMin.y = 0.0f;
	}
	if (tpMax.x > m_mapSize.x) {
		tpMax.x = m_mapSize.x;
	}
	if (tpMax.y > m_mapSize.y) {
		tpMax.y = m_mapSize.y;
	}
	glm::vec2 testPT = glm::vec2 (0.0);
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> disY(tpMin.x, tpMax.x);
	std::uniform_real_distribution<float> disX(tpMin.y, tpMax.y);

	for (int i = 0; i < 10; i++)
	{
		testPT.x = disY(gen);   	
		testPT.y = disX(gen);   

		char result;
		result = m_levelManager->get_character(testPT, true);

		bool posCheck = collision_Check(result);
		if (glm::length(testPT - playerP) <= 200.0f) posCheck = true;
		if (posCheck == false) {
			verifiedPosition = testPT;
			return testPT;
		}
	}
	return verifiedPosition;
}


void ZombieManager::init(LevelManager& levelManager, 
	CharacterManager& characterManager, 
	CollisionManager& collisionManager, 
	SoundDelegate& sound,
	ParticleManager& particleManager)
{
	m_levelManager				= &levelManager;
	m_characterManager			= &characterManager;
	m_collisionManager			= &collisionManager;
	soundDelegate				= &sound;
	m_mapSize					= levelManager.get_map_size() * glm::vec2(75.0f);
	m_blacklistedChar			= levelManager.get_restricted_tiles();
	m_tileSize					= levelManager.get_tile_dimensions();
	minDistBetweenSprites		= m_characterManager->get_sprite_radius() * 2.0f;
	m_minBulletCollisionDist	= m_characterManager->get_sprite_radius() + (7.0f / 2.0f); // 7.0 is the bullet diameter
	m_particleManager			= &particleManager;
	start = std::chrono::steady_clock::now();
	m_waveStartSoundKey = sound.get_key("Start_Sounds_001.wav");
}


void ZombieManager::spawn_Wave(int wave)
{
	//m_zombies.clear();
	int numZombies = 6 * (wave) + 5;
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> disX(1.0f, 2.8f);

	for (int i = 0; i < numZombies; i++) 	{
		m_zombies.push_back(Zombie());
		m_zombies.back().position = calculate_spawnPosition();   //sets position to newest zombie using calcspawn function
		m_zombies.back().speed = disX(rd);
		m_zombies.back().isAlive = true;
	}
}

void ZombieManager::collide_with_player(Zombie& zombie)
{
	// Get distance from center to center
	float dist_a_to_b = glm::length(m_characterManager->m_player.position - zombie.position);
	if (dist_a_to_b < minDistBetweenSprites) {
		glm::vec2 normalizedAngle = glm::normalize(m_characterManager->m_player.position - zombie.position);
		float collisionDepth = minDistBetweenSprites - dist_a_to_b;
		glm::vec2 push = normalizedAngle * collisionDepth;

		m_characterManager->m_player.position += push / 2.0f;
		zombie.position -= push / 2.0f;
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
	std::chrono::steady_clock::time_point local_time_PT = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(local_time_PT - start);
	if (elapsed_seconds.count() >= 20)
	{
		soundDelegate->play_effect(m_waveStartSoundKey);
		start = std::chrono::steady_clock::now();
		return true;
	}
	return false;
}


void ZombieManager::update() {
	if (should_spawn_wave() == true) {
		spawn_Wave(wave++);
	}
	// If false, zombies are still alive so play a sound (roll a dice)
	else {
		if (rand() % 600 < 3 && m_characterManager->m_player.isAlive) {
			soundDelegate->play_effect(m_zombieSoundKeys[rand() % 10]);
		}
	}


	float playerX = m_characterManager->m_player.position.x;
	float playerY = m_characterManager->m_player.position.y;

	//update the zombie position variables
	for (auto& it : m_zombies) {
		if (!it.isAlive) {
			continue;
		}
		if (it.health <= 0.0f) {
			it.isAlive = false;
			m_characterManager->m_player.zombieKills++;
		}
		float angleRads = atan2(it.position.y - playerY, it.position.x - playerX);
		float angleDegrees = angleRads * 180.0f / 3.14157f;
		it.position -= glm::vec2(cos(angleRads), sin(angleRads)) * it.speed;
		it.angle = angleDegrees;
		damage_player(it);
		tile_collision(it);
		collide_with_player(it);
		perform_collisions(it);

		// ================================================
		// PARTICLE COLLISION
		// ================================================
		for (auto& particle : m_particleManager->m_particles) {
			// Must keep color.r == 0 to stop simulating blood particles!
			if (particle.isActive && particle.m_color.r == 0) {
				float dist_a_to_b = glm::length(it.position - particle.position);
				if (dist_a_to_b < m_minBulletCollisionDist) {
					particle.isActive = false;
					particle.health = 0.0;
					m_particleManager->blood_particle(particle.position, particle.angle);
					it.health -= m_characterManager->get_gun_damage();
					if (it.health <= 0.0) {
						m_characterManager->m_player.money += m_characterManager->m_economy.zombieKill;
						break;
					}
				}
			}
		}

	}
}

void ZombieManager::tile_collision(Zombie& zombie) {
	glm::vec2 worldSize = m_levelManager->get_map_size();
	CollisionPosition collisionAreas[4];
	collisionAreas[0].position = zombie.position; //TL
	collisionAreas[1].position = zombie.position; //TR
	collisionAreas[2].position = zombie.position; //BL
	collisionAreas[3].position = zombie.position; //BR

	collisionAreas[0].position.x	-= dim.x;
	collisionAreas[0].position.y	+= dim.y;
	collisionAreas[2].position		-= dim;
	collisionAreas[1].position		+= dim;
	collisionAreas[3].position.x	+= dim.x;
	collisionAreas[3].position.y	-= dim.y;

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

void ZombieManager::reset()
{
	wave = 0;
	m_zombies.clear();
	start = std::chrono::steady_clock::now();

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

void ZombieManager::perform_collisions(Zombie& zombie) {
	// This logic is saying that zombie is colliding with zombie j
	for (auto& zombie2 : m_zombies) {
		if (&(zombie2) != &(zombie)) {
			// Get distance from center to center
			float dist_a_to_b = glm::length(zombie.position - zombie2.position);
			if (dist_a_to_b < minDistBetweenSprites) {
				glm::vec2 normalizedAngle = glm::normalize(zombie.position - zombie2.position);
				float collisionDepth = minDistBetweenSprites - dist_a_to_b;
				glm::vec2 push = normalizedAngle * collisionDepth;
				zombie.position += push / 2.0f;
				zombie2.position -= push / 2.0f;
			}
		}
		
	}
}

void ZombieManager::damage_player(Zombie& zombie)
{
	float distance = glm::length(m_characterManager->m_player.position - zombie.position);

	if (distance <= minDistBetweenSprites + 15.0f) {
		m_characterManager->damage_player(0.3f);
	}
}
