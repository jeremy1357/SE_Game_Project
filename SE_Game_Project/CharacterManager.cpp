#include "CharacterManager.h"
#include "CharacterManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include <SDL/SDL.h>
#include<iostream>


CharacterManager::CharacterManager()
{
	this->m_player.health = 100;
}


CharacterManager::~CharacterManager()
{

}

int CharacterManager::GetHealth()
{
	return this->m_player.health;
}

void CharacterManager::Damage(int amount)
{
	this->m_player.health -= amount;
}

string CharacterManager::GetName()
{
	return this->m_player.name;
}

void CharacterManager::SetName(string name)
{
	this->m_player.name = name;
}

bool CharacterManager::is_player_alive()
{
	return m_player.isAlive;
}

bool CharacterManager::collisionCheck(char parameter)
{
	for (int i = 0; i < blacklistedChar.size(); i++) {
		if (blacklistedChar[i] == parameter) {
			return true;
		}
	}
	return false;
}

void CharacterManager::init(InputManager& inputManager, LevelManager& levelManager)
{
	m_inputManager = &inputManager;
	m_levelManager = &levelManager;
	blacklistedChar.push_back('#');

}

void CharacterManager::update()
{
	if (m_player.health < 0)
	{
		m_player.isAlive = false;
	}
	else
	{
		m_player.isAlive = true;

		if (m_inputManager->get_key(SDLK_w))
		{
			glm::vec2 temp = m_player.position;
			temp.y += 5.0f;
			char stepChar = m_levelManager->get_character(temp, true);
			if (collisionCheck(stepChar) == false)
			{
				m_player.position.y += 5.0f;
			}
			else
			{
				m_player.position.y += 0.0f;
			}
		}
		if (m_inputManager->get_key(SDLK_s))
		{
			glm::vec2 temp = m_player.position;
			temp.y += -5.0f;
			char stepChar = m_levelManager->get_character(temp, true);
			if (collisionCheck(stepChar) == false)
			{
				m_player.position.y += -5.0f;
			}
			else
			{
				m_player.position.y += 0.0f;
			}
		}
		if (m_inputManager->get_key(SDLK_a))
		{
			glm::vec2 temp = m_player.position;
			temp.x += -5.0f;
			char stepChar = m_levelManager->get_character(temp, true);
			if (collisionCheck(stepChar) == false)
			{
				m_player.position.x += -5.0f;
			}
			else
			{
				m_player.position.x += 0.0f;
			}
		}
		if (m_inputManager->get_key(SDLK_d))
		{
			glm::vec2 temp = m_player.position;
			temp.x += 5.0f;
			char stepChar = m_levelManager->get_character(temp, true);
			if (collisionCheck(stepChar) == false)
			{
				m_player.position.x += 5.0f;
			}
			else
			{
				m_player.position.x += 0.0f;
			}
		}

	}
}
