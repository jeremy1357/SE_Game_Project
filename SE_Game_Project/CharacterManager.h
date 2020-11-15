
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "InputManager.h"
#include "LevelManager.h"
#include "ZombieManager.h"
#include "GameEconomy.hpp"
#include "Camera.h"
#include "ParticleManager.h"
#include "SoundDelegate.h"

#include <vector>

using namespace std;


struct Player {
	string name = "Steve";
	int health = 100;
	bool isAlive = true;
	float angle = 0.0f;
	glm::vec2 position = glm::vec2(0,0);
	int money = 500;
};

class CharacterManager
{
	public:
		CharacterManager();
		~CharacterManager();
		string GetName();
		int GetHealth();

		void Damage(int amount);
		void SetName(string n);
		void init(InputManager& inputManager, 
			LevelManager& levelManager, 
			CollisionManager& collisionManager,
			Camera& camera,
			SoundDelegate& soundDelegate,
			const glm::vec2& playerPos,
			const std::string& programDirectory);
		void update();
		void tile_collision();
		bool is_player_alive();
		void add_item_to_inventory(const std::string& itemName);
		void set_gun_index(const std::string& itemName);
		std::string get_gun_name();

		Player m_player;
		ZombieManager m_zombieManager;
		GameEconomy m_economy;
		ParticleManager m_particleManager;
	private:
		struct CollisionPosition {
			glm::vec2 position;
			bool didCollisionOccur = false;
		};

		bool collisionCheck(char parameter);
		void perform_tile_collision(CollisionPosition* cp);


		// This should be half of player square dimensions
		const glm::vec2 dim = glm::vec2(25.0f);
		InputManager* m_inputManager			= nullptr;
		LevelManager* m_levelManager			= nullptr;
		Camera* m_camera						= nullptr;
		SoundDelegate* m_soundDelegate			= nullptr;
		CollisionManager* m_collisionManager	= nullptr;


		std::vector<char> blacklistedChar;
		std::vector<Item> m_inventory;
		int m_currentGunIndex = -1;

};

