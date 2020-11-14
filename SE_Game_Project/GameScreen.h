// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include "Screen.hpp"
#include "GameCollision.h"
#include "SpriteRenderer.h"
#include "CharacterManager.h"
#include "TextureCache.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "GameEconomy.hpp"

class GameScreen : public Screen
{
public:
	GameScreen(int uniqueScreenID);
	virtual void on_init()   override;
	virtual void on_entry()	 override;
	virtual void on_exit() 	 override;
	virtual void on_render() override;
	virtual void on_update() override;


private:
	// DECLARE YOUR OBJECTS HERE
	// Can be used by any member function of this class
	SpriteRenderer m_spriteRenderer;
	TextureCache m_textureCache;
	LevelManager m_levelManager;
	CharacterManager m_characterManager;
	CollisionManager m_collisionManager;
	GameEconomy m_economy;

};
