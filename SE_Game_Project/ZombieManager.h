#pragma once
#include <string>
#include <glm/glm.hpp>
#include "LevelManager.h"
#include "CollisionManager.h"
#include <vector>

using namespace std;


class CharacterManager;

struct Zombie {
	int health = 100;
	bool isAlive = true;
	glm::vec2 position = glm::vec2(0.0);
	float angle = 0.0;
	float radius = 25.0f;
};

class ZombieManager
{
public:
	ZombieManager();
	~ZombieManager();

	int wave = 0;

	void update();
	void init(LevelManager& levelManager, CharacterManager& characterManager, const std::vector<char> blacklistedTiles, int mapSizex, int mapSizey, glm::vec2 tileSize, CollisionManager& collisionManager);
	bool collision_Check(char parameter);
	void tile_collision();
	std::vector<Zombie> m_zombies;

private:


	int m_mapSizex;
	int m_mapSizey;
	glm::vec2 m_tileSize = glm::vec2(75.0f, 75.0f);
	glm::vec2 calculate_spawnPosition();
	float m_speed; 

	struct CollisionPosition {
		glm::vec2 position;
		bool didCollisionOccur = false;
	};

	void npc_collision();
	bool should_spawn_wave();
	void spawn_Wave(int wave);
	const glm::vec2 dim = glm::vec2(25.0f);

	LevelManager* m_levelManager = nullptr;
	CharacterManager* m_characterManager = nullptr;
	CollisionManager* m_collisionManager = nullptr;

	std::vector<char> m_blacklistedChar;
	
	void perform_tile_collision(CollisionPosition* cp);


};