#include "CharacterManager.h"
#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	this->health = 100;
}

CharacterManager::CharacterManager(string n)
{
	this->health = 100;
	this->name = n;
}

CharacterManager::~CharacterManager()
{

}

int CharacterManager::GetHealth()
{
	return this->health;
}

void CharacterManager::Damage(int amount)
{
	this->health -= amount;
}

string CharacterManager::GetName()
{
	return this->name;
}

void CharacterManager::SetName(string n)
{
	this->name = n;
}