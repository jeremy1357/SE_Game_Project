#ifndef CharacterManager_H
#define CharacterManager_H
#endif
#pragma once
#include<iostream>
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
	private:
		int health;
		string name;

};

