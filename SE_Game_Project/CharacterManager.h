
#pragma once

#include <string>

using namespace std;


struct Player {
	string m_name;
	int m_health;
	bool status;
};

class CharacterManager
{
	public:
		CharacterManager();
		CharacterManager(string n);
		~CharacterManager();

		int GetHealth();
		void Damage(int amount);
		string GetName();
		void SetName(string n);
		bool is_player_alive();

		bool status;
		int m_health;
		string m_name;

};

