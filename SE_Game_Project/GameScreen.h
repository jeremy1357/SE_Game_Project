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
	void render_game_screen();
	SpriteRenderer m_spriteRenderer;
	TextureCache m_textureCache;
	LevelManager m_levelManager;
	CharacterManager m_characterManager;
	CollisionManager m_collisionManager;
	bool m_isInventoryFocused = false;
};
