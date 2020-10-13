
#pragma once

#include <string>

using namespace std;

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

		int m_health;
		string m_name;

};

