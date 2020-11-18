#pragma once
#include <string>
#include <glm/glm.hpp>
#include "LevelManager.h"
#include "CollisionManager.h"
#include "SoundDelegate.h"

#include <vector>
using namespace std;

class CharacterManager;

struct Zombie {
	int health = 100;
	bool isAlive = true;
	glm::vec2 position = glm::vec2(0.0);
	float angle = 0.0;
	float radius = 20.0f;
	float speed = 0.0;
};

class ZombieManager {
public:
	ZombieManager();
	~ZombieManager();
	void update();
	void init(LevelManager& levelManager,
		CharacterManager& characterManager,
		CollisionManager& collisionManager,
		SoundDelegate& sound);
	void set_zombie_sound_keys(int min, int max);
	bool collision_Check(char parameter);
	void tile_collision();


	std::vector<Zombie> m_zombies;
	int wave = 0;
private:
	void npc_collision();
	bool should_spawn_wave();
	void spawn_Wave(int wave);
	void collide_with_player(Zombie* zombie);

	int m_mapSizex;
	int m_mapSizey;
	glm::vec2 m_tileSize = glm::vec2(75.0f, 75.0f);
	glm::vec2 m_mapSize;
	glm::vec2 calculate_spawnPosition();
	float minDistBetweenSprites = 0.0f;

	struct CollisionPosition {
		glm::vec2 position;
		bool didCollisionOccur = false;
	};


	const glm::vec2 dim = glm::vec2(25.0f);

	LevelManager* m_levelManager = nullptr;
	CharacterManager* m_characterManager = nullptr;
	CollisionManager* m_collisionManager = nullptr;
	SoundDelegate* soundDelegate = nullptr;
	std::vector<char> m_blacklistedChar;
	std::vector<int> m_zombieSoundKeys;
	void perform_tile_collision(CollisionPosition* cp);


};