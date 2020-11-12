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
	void render(glm::vec2 playerPosition, glm::vec2 windowDimensions);
	char get_character(glm::vec2 position, bool shouldScale);
	glm::vec2 get_tile_center(glm::vec2 tileToGetCenterOf);
	bool is_tile_restricted(const glm::vec2& point);
	std::vector<char> get_restricted_tiles() const { return m_restrictedTiles; }
	bool unlock_tile(glm::vec2 point);

	glm::vec2 get_map_size()		const { return mapSize; }
	glm::vec2 get_tile_dimensions() const { return m_tileDimensions; }
private:
	GLuint get_texture_ID(const char& key);


	TextureCache* m_textureCache	= nullptr;
	std::string m_projectDirectory	= "";
	SpriteRenderer* m_renderer		= nullptr;
	bool m_needsRender				= true; // Start at true

	const glm::vec2 m_tileDimensions = glm::vec2(75.0f, 75.0f);
	std::vector<char> m_restrictedTiles; // These are tiles that the player cant move across
	std::vector<std::vector<char>> m_mapData;
	std::map<char, GLuint> m_textureLookup;
	glm::vec2 mapSize; // This needs to be calculated during map load in stage
};

