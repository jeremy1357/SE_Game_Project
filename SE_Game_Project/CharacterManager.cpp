#include "CharacterManager.h"
#include "CharacterManager.h"

#include<iostream>

CharacterManager::CharacterManager()
{
	this->m_Player.health = 100;
}


CharacterManager::~CharacterManager()
{

}

int CharacterManager::GetHealth()
{
	return this->m_Player.health;
}

void CharacterManager::Damage(int amount)
{
	this->m_Player.health -= amount;
}

string CharacterManager::GetName()
{
	return this->m_Player.name;
}

void CharacterManager::SetName(string name)
{
	this->m_Player.name = name;
}

bool CharacterManager::is_player_alive()
{
	if (m_Player.health < 0)
		return m_Player.isAlive == false;
	else
		return m_Player.isAlive == true;
}

void CharacterManager::update()
{

}
