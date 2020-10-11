#pragma once
#include <vector>

class LevelManager
{
public:
	LevelManager();
	void onInit();
	void onUpdate();
	void onRender();

private:
	std::vector<std::vector<char>> m_map;


};

