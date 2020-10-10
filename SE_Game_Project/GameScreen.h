// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include "Screen.hpp"

class GameScreen : public Screen
{
public:
	GameScreen(int uniqueScreenID);
	virtual void init()		override;
	virtual void onEntry()	override;
	virtual void onExit()	override;
	virtual void onRender() override;
	virtual void onUpdate() override;


private:
	// DECLARE YOUR OBJECTS HERE
	// Can be used by any member function of this class
	// EX) SomeManager aGoodName;

};
