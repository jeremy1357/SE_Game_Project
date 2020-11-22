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
	void render_shop();
	void render_inventory();
	void render_widget1();
	void render_widget2();

	CharacterManager m_characterManager;
	SpriteRenderer m_spriteRenderer;
	TextureCache m_textureCache;
	LevelManager m_levelManager;
	CollisionManager m_collisionManager;
	bool m_isInventoryFocused = false;
};
