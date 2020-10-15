#pragma 
#include "Screen.hpp"

class SettingsScreen : public Screen
{
public:
	SettingsScreen(int uniqueScreenID);
	virtual void on_init()   override;
	virtual void on_entry()	 override;
	virtual void on_exit()	 override;
	virtual void on_render() override;
	virtual void on_update() override;

private:


};

