
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
#include "Score.h"

#include <vector>

using namespace std;


struct Player {
	string name			= "Steve";
	float health		= 100.0f;
	bool isAlive		= false;
	float angle			= 0.0f;
	glm::vec2 position	= glm::vec2(0,0);
	int money			= 500;
	int zombieKills		= 0;
	int armor			= 0;
	bool armorEquipped	= false;
	int armorIndex	    = -1;
};


class CharacterManager
{
	public:
		CharacterManager();
		~CharacterManager();
		string GetName();
		int GetHealth();
		void start_game(std::string name);

		void Damage(int amount);
		void SetName(string n);
		void init(InputManager& inputManager, 
			LevelManager& levelManager, 
			CollisionManager& collisionManager,
			Camera& camera,
			SoundDelegate& soundDelegate,
			const std::string& programDirectory,
			std::vector<Score>& scores);
		void update(float playerAngle, bool isImGuiHovered);
		void tile_collision();
		bool is_player_alive();
		void add_item_to_inventory(const std::string& itemName);
		void use_consumable_item(const std::string& itemName);
		void attempt_to_buy_item(const std::string& itemName);
		void attempt_to_sell_item(const std::string& itemName);
		void set_player_hurt_sound_ranges(int min, int max);
		void stop_game_over_music();
		void use_consumable(const std::string& itemName);
		void toggleEquippableItem(const std::string& itemName);
		void set_gun_index(const std::string& itemName);
		float get_sprite_radius() { return m_spriteRadius; }
		float get_gun_damage() { return m_inventory[m_currentGunIndex].damage; }
		void damage_player(float damage);
		std::string get_gun_name();


		Player m_player;
		ZombieManager m_zombieManager;
		GameEconomy m_economy;
		ParticleManager m_particleManager;
		std::vector<Item> m_inventory;
		std::vector<Score>* m_scores;

	private:
		struct CollisionPosition {
			glm::vec2 position;
			bool didCollisionOccur = false;
		};

		bool collisionCheck(char parameter);
		void perform_tile_collision(CollisionPosition* cp);


		// This should be half of player square dimensions
		//const glm::vec2 dim = glm::vec2(25.0f);
		float m_spriteRadius = 25.0f;
		const glm::vec2 PLAYER_START_POINT = glm::vec2(600.0f, 1875.0f);
		InputManager* m_inputManager			= nullptr;
		LevelManager* m_levelManager			= nullptr;
		Camera* m_camera						= nullptr;
		SoundDelegate* m_soundDelegate			= nullptr;
		CollisionManager* m_collisionManager	= nullptr;


		std::vector<char> blacklistedChar;
		int m_currentGunIndex = -1;

		// Sound stuff
		int m_characterSoundHurtMin = 0;
		int m_characterSoundHurtMax = 0;
		bool m_gameoverMusicPlaying = false;
};

