#pragma once
#include <string>
#include <glm/glm.hpp>
#include "LevelManager.h"
#include <vector>

using namespace std;


class CharacterManager;

struct Zombie {
	int health = 100;
	bool isAlive = true;
	glm::vec2 position = glm::vec2(0.0);
	float angle = 0.0;
};

class ZombieManager
{
public:
	ZombieManager();
	~ZombieManager();

	int wave = 0;

	void update();
	void init(LevelManager& levelManager,CharacterManager& characterManager, const std::vector<char> blacklistedTiles, int mapSizex, int mapSizey, glm::vec2 tileSize);
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

	bool should_spawn_wave();
	void spawn_Wave(int wave);
	const glm::vec2 dim = glm::vec2(25.0f);
	LevelManager* m_levelManager = nullptr;
	CharacterManager* m_characterManager = nullptr;
	std::vector<char> m_blacklistedChar;
	
	void perform_tile_collision(CollisionPosition* cp);


};