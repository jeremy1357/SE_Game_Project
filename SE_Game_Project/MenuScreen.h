#pragma once
#include "Screen.hpp"
#include "MenuEffects.h"


class MenuScreen : public Screen
{
public:
	MenuScreen(int uniqueScreenID);
	virtual void on_init()   override;
	virtual void on_entry()	 override;
	virtual void on_exit()	 override;
	virtual void on_render() override;
	virtual void on_update() override;

	char buf1[64];

private:
	MenuEffects m_menuEffects;
};

