#include "CharacterManager.h"
#include "CharacterManager.h"

#include<iostream>

CharacterManager::CharacterManager()
{
	this->m_health = 100;
}

CharacterManager::CharacterManager(string n)
{
	this->m_health = 100;
	this->m_name = n;
}

CharacterManager::~CharacterManager()
{

}

int CharacterManager::GetHealth()
{
	return this->m_health;
}

void CharacterManager::Damage(int amount)
{
	this->m_health -= amount;
}

string CharacterManager::GetName()
{
	return this->m_name;
}

void CharacterManager::SetName(string n)
{
	this->m_name = n;
}

bool CharacterManager::is_player_alive()
{
	if (m_health < 0)
		return false;
	else
		return true;
}
