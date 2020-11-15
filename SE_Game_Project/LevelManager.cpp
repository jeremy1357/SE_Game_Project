#include "LevelManager.h"
#include <fstream>
#include <iostream>


LevelManager::LevelManager() {
	// Empty
}

void LevelManager::init(
	const std::string& projectDirectory, 
	SpriteRenderer& renderer, 
	TextureCache& textureCache) 
{
	m_renderer = &renderer;
	m_textureCache = &textureCache;
	m_projectDirectory = projectDirectory + "Resources\\Maps\\";
	std::string mapPath = m_projectDirectory + "map1.txt";
	std::vector <unsigned char> mapData;

	std::ifstream file(mapPath, std::ios::binary | std::ios::in);

	if (file.fail()) {
		perror(mapPath.c_str());
		return;
	}
	file.seekg(0, std::ios::end);
	// Get the size of the file
	int fileSize = file.tellg();
	// Seek back to beginning
	file.seekg(0, std::ios::beg);
	// Make sure we dont count the file header in the file size
	fileSize -= file.tellg();
	// Resize the given buffer to the filesize
	mapData.resize(fileSize);
	file.read((char*)&(mapData[0]), fileSize);
	file.close();

	int row = 0;
	m_mapData.push_back(std::vector<char>());
	for (size_t i = 0; i < mapData.size(); i++) {
		if (mapData[i] == '\n') {
			row += 1;
			m_mapData.push_back(std::vector<char>());
		}
		m_mapData[row].push_back(mapData[i]);
	}
	
	mapSize.x = m_mapData.size();
	mapSize.y = m_mapData[0].size();
	std::string imageDirectory = projectDirectory + "Resources\\Textures\\";

	GLuint poundTexture		= m_textureCache->get_texture_id(imageDirectory + "Ground_01.png");
	GLuint grassTexture		= m_textureCache->get_texture_id(imageDirectory + "Dirt_01.png");
	GLuint percentTexture	= m_textureCache->get_texture_id(imageDirectory + "Ground_04.png");
	GLuint moneySignTexture = m_textureCache->get_texture_id(imageDirectory + "Dirt_02.png");
	GLuint atTexture = m_textureCache->get_texture_id(imageDirectory + "dark_crate_five.png");
	GLuint starTexture = m_textureCache->get_texture_id(imageDirectory + "log2.png");
	GLuint dTexture = m_textureCache->get_texture_id(imageDirectory + "sand.png");
	GLuint wTexture = m_textureCache->get_texture_id(imageDirectory + "LAVA.png");
	GLuint qTexture = m_textureCache->get_texture_id(imageDirectory + "grass.png");

	//For missing textures
	GLuint nullTexture = m_textureCache->get_texture_id(imageDirectory + "missing.png");

	m_textureLookup.insert(std::make_pair('#', poundTexture)); // Cobbles
	m_textureLookup.insert(std::make_pair('-', grassTexture)); // Dirt 1; ironically not grass
	m_textureLookup.insert(std::make_pair('%', percentTexture)); // Mossy Cobbles
	m_textureLookup.insert(std::make_pair('$', moneySignTexture)); // Dirt 2
	m_textureLookup.insert(std::make_pair('@', atTexture)); // Crate
	m_textureLookup.insert(std::make_pair('*', starTexture)); // Wood log
	m_textureLookup.insert(std::make_pair('d', dTexture)); // Sand
	m_textureLookup.insert(std::make_pair('w', wTexture)); // Lava
	m_textureLookup.insert(std::make_pair('o', nullTexture));
	m_textureLookup.insert(std::make_pair('&', nullTexture));
	m_textureLookup.insert(std::make_pair('=', nullTexture));
	m_textureLookup.insert(std::make_pair('q', qTexture)); // No texture yet/error texture

	m_textureLookup.insert(std::make_pair('~',nullTexture)); // No texture yet/error texture
	// Manually add in restricted tiles here. These cant me moved on
	m_restrictedTiles.push_back('#');
	m_restrictedTiles.push_back('%');
	m_restrictedTiles.push_back('q');

}

void LevelManager::render(glm::vec2 playerPosition, glm::vec2 windowDimensions) {
	if (m_needsRender) {
		m_needsRender = false;
		// Verify that the renderer has been properly initialized with a non-nullptr value
		if (m_renderer == nullptr) {
			return;
		}
		glm::vec2 tileCenter(0.0f, 0.0f);
		for (auto& x : m_mapData) {
			for (auto& y : x) {
				switch (y) {
				case '#':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('#'));
					break;
				case '-':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('-'));
					break;
				case '%':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('%'));
					break;
				case '$':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('$'));
					break;
				case '@':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('@'));
					break;
				case '*':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('*'));
					break;
				case 'w':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('w'));
					break;
				case 'd':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('d'));
					break;
				case 'q':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('q'));
					break;
				default:
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('~'));
					break;
					// Maybe add a texture showing ERROR
				}
				tileCenter.y += 1.0f;
			}
			tileCenter.x += 1.0f;
			tileCenter.y = 0.0f;
		}
	}
}

char LevelManager::get_character(glm::vec2 position, bool shouldScale)
{
	if (shouldScale) {
		position /= m_tileDimensions;
	}
	int xPos = (int)floor(position.x);
	int yPos = (int)floor(position.y);
	if (m_mapData.size() > xPos && xPos >= 0) {
		if (m_mapData[xPos].size() > yPos && yPos >= 0) {
			return m_mapData[xPos][yPos];
		}
	}
	return '\0';
}

bool LevelManager::is_tile_restricted(const glm::vec2& point) {
	char tile = get_character(point, true);
	for (int i = 0; i < m_restrictedTiles.size(); i++) {
		if (tile == m_restrictedTiles[i]) {
			return true;
		}
	}
	return false;
}

bool LevelManager::unlock_tile(glm::vec2 point)
{
	point /= m_tileDimensions;

	const char DOOR = 'q';
	int xPos = (int)floor(point.x);
	int yPos = (int)floor(point.y);
	if (m_mapData.size() > xPos && xPos >= 0) {
		if (m_mapData[xPos].size() > yPos && yPos >= 0) {
			if (m_mapData[xPos][yPos] == DOOR) {
				m_mapData[xPos][yPos] = '@';
				m_needsRender = true;
				m_renderer->require_static_redraw();
				return true;
			}
		}
	}
	return false;
}

glm::vec2 LevelManager::get_tile_center(glm::vec2 tileToGetCenterOf)
{
	glm::vec2 tempTile = tileToGetCenterOf / m_tileDimensions;
	int xPos = (int)floor(tempTile.x);
	int yPos = (int)floor(tempTile.y);
	tileToGetCenterOf.x = xPos * m_tileDimensions.x;
	tileToGetCenterOf.y = yPos * m_tileDimensions.y;

	if (m_mapData.size() > xPos && xPos >= 0) {
		if (m_mapData[xPos].size() > yPos && yPos >= 0) {
			glm::vec2 bl = tileToGetCenterOf + (m_tileDimensions / 2.0f);
			return bl;
		}
	}
}

GLuint LevelManager::get_texture_ID(const char& key)
{
	std::map<char, GLuint>::iterator it = m_textureLookup.find(key);
	if (it != m_textureLookup.end()) {
		return it->second;
	}
	return 0;
}