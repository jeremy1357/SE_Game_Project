
#pragma once

#include <string>
#include<glm/glm.hpp>

using namespace std;


struct Player {
	string name = "Steve";
	int health = 100;
	bool isAlive = true ;
	glm::vec2 direction = glm::vec2(1,0);
	glm::vec2 position = glm::vec2(0);
	int money = 500;
};

class CharacterManager
{
	public:
		CharacterManager();
		~CharacterManager();

		int GetHealth();
		void Damage(int amount);
		string GetName();
		void SetName(string n);
		bool is_player_alive();

		void update();

		Player m_Player;

};

