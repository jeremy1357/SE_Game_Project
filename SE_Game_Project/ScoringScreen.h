#pragma once
#include "Screen.hpp"

class ScoringScreen : public Screen
{
public:
	ScoringScreen(int uniqueScreenID);
	virtual void on_init()   override;
	virtual void on_entry()	 override;
	virtual void on_exit() 	 override;
	virtual void on_render() override;
	virtual void on_update() override;
private:

};

