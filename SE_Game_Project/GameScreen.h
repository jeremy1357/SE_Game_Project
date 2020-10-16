// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include "Screen.hpp"
#include "GameCollision.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "CharacterManager.h"
#include "GameCollision.h"
#include "TextureCache.h"
#include "LevelManager.h"

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
	// EX) SomeManager aGoodName;
	SpriteRenderer m_spriteRenderer;
	Camera m_camera;
	TextureCache m_textureCache;
	LevelManager m_levelManager;
	//ParticleManager m_particleManager;

};
