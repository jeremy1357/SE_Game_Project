#pragma once
#include <vector>
#include <string>
#include "SpriteRenderer.h"
#include <glm/glm.hpp>

class LevelManager
{
public:
	LevelManager();
	void init(const std::string& projectDirectory, SpriteRenderer& renderer);
	void update();
	void render();

private:
	glm::vec2 tileSize = glm::vec2(30.0f, 30.0f);
	std::vector<std::vector<char>> m_map;
	std::string m_projectDirectory = "";
	SpriteRenderer* m_renderer = nullptr;
};

