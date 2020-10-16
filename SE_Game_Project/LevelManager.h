#pragma once
#include <vector>
#include <string>
#include "SpriteRenderer.h"
#include "TextureCache.h"
#include <glm/glm.hpp>
#include <map>

class LevelManager
{
public:
	LevelManager();
	void init(const std::string& projectDirectory, SpriteRenderer& renderer, TextureCache& textureCache);
	void update();
	void render(glm::vec2 playerPosition, glm::vec2 windowDimensions);

private:
	GLuint get_texture_ID(const char& key);

	TextureCache* m_textureCache = nullptr;
	glm::vec2 m_tileSize = glm::vec2(30.0f, 30.0f);
	std::vector<std::vector<char>> m_mapData;
	std::string m_projectDirectory = "";
	SpriteRenderer* m_renderer = nullptr;
	std::map<char, GLuint> m_textureLookup;
};

