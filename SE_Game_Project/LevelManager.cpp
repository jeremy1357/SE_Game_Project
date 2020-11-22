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
	// Create a copy of the map data for when we need to reset the map
	m_originalMapData = m_mapData;
	mapSize.x = m_mapData.size();
	mapSize.y = m_mapData[0].size();
	std::string imageDirectory = projectDirectory + "Resources\\Textures\\";

	GLuint poundTexture		= m_textureCache->get_texture_id(imageDirectory + "Ground_01.png");
	GLuint dirtTexture		= m_textureCache->get_texture_id(imageDirectory + "dirt.png");
	GLuint percentTexture	= m_textureCache->get_texture_id(imageDirectory + "Ground_04.png");
	GLuint equalsTexture = m_textureCache->get_texture_id(imageDirectory + "Ground_05.png");
	GLuint moneySignTexture = m_textureCache->get_texture_id(imageDirectory + "Dirt_02.png");
	GLuint atTexture = m_textureCache->get_texture_id(imageDirectory + "dark_crate_five.png");
	GLuint starTexture = m_textureCache->get_texture_id(imageDirectory + "log2.png");
	GLuint dTexture = m_textureCache->get_texture_id(imageDirectory + "sand.png");
	GLuint wTexture = m_textureCache->get_texture_id(imageDirectory + "lava.png");
	GLuint qTexture = m_textureCache->get_texture_id(imageDirectory + "door.png");
	GLuint tTexture = m_textureCache->get_texture_id(imageDirectory + "tile.png");
	GLuint cTexture = m_textureCache->get_texture_id(imageDirectory + "concrete.png");
	GLuint ampTexture = m_textureCache->get_texture_id(imageDirectory + "wasteland.png");
	GLuint pTexture = m_textureCache->get_texture_id(imageDirectory + "lava_n.png");
	GLuint oTexture = m_textureCache->get_texture_id(imageDirectory + "lava_s.png");
	GLuint kTexture = m_textureCache->get_texture_id(imageDirectory + "lava_e.png");
	GLuint jTexture = m_textureCache->get_texture_id(imageDirectory + "lava_w.png");
	GLuint bTexture = m_textureCache->get_texture_id(imageDirectory + "lava_ne.png");
	GLuint iTexture = m_textureCache->get_texture_id(imageDirectory + "lava_nw.png");
	GLuint nTexture = m_textureCache->get_texture_id(imageDirectory + "lava_se.png");
	GLuint lTexture = m_textureCache->get_texture_id(imageDirectory + "lava_sw.png");
	GLuint vTexture = m_textureCache->get_texture_id(imageDirectory + "lava_ne_i.png");
	GLuint uTexture = m_textureCache->get_texture_id(imageDirectory + "lava_nw_i.png");
	GLuint mTexture = m_textureCache->get_texture_id(imageDirectory + "lava_se_i.png");
	GLuint hTexture = m_textureCache->get_texture_id(imageDirectory + "lava_sw_i.png");
	GLuint carrotTexture = m_textureCache->get_texture_id(imageDirectory + "grass.png");
	GLuint rTexture = m_textureCache->get_texture_id(imageDirectory + "grass_n.png");
	GLuint eTexture = m_textureCache->get_texture_id(imageDirectory + "grass_ne.png");
	GLuint fTexture = m_textureCache->get_texture_id(imageDirectory + "grass_nw.png");
	GLuint yTexture = m_textureCache->get_texture_id(imageDirectory + "grass_ne_i.png");
	GLuint xTexture = m_textureCache->get_texture_id(imageDirectory + "grass_nw_i.png");
	//For missing textures
	GLuint nullTexture = m_textureCache->get_texture_id(imageDirectory + "missing.png");

	m_textureLookup.insert(std::make_pair('#', poundTexture)); // Cobbles
	m_textureLookup.insert(std::make_pair('-', dirtTexture)); // Dirt;
	m_textureLookup.insert(std::make_pair('%', percentTexture)); // Mossy Cobbles
	m_textureLookup.insert(std::make_pair('$', moneySignTexture)); // Dirt 2
	m_textureLookup.insert(std::make_pair('@', atTexture)); // Crate
	m_textureLookup.insert(std::make_pair('*', starTexture)); // Wood log
	m_textureLookup.insert(std::make_pair('d', dTexture)); // Sand
	m_textureLookup.insert(std::make_pair('w', wTexture)); // Lava
	m_textureLookup.insert(std::make_pair('c', cTexture)); // Concrete wall
	m_textureLookup.insert(std::make_pair('t', tTexture)); // Tile
	m_textureLookup.insert(std::make_pair('&', ampTexture)); // Wasteland
	m_textureLookup.insert(std::make_pair('p', pTexture)); // North lava
	m_textureLookup.insert(std::make_pair('o', oTexture)); // South lava
	m_textureLookup.insert(std::make_pair('k', kTexture)); // East lava
	m_textureLookup.insert(std::make_pair('j', jTexture)); // West lava
	m_textureLookup.insert(std::make_pair('b', bTexture)); // Northeast lava
	m_textureLookup.insert(std::make_pair('i', iTexture)); // Northwest lava
	m_textureLookup.insert(std::make_pair('n', nTexture)); // Southeast lava
	m_textureLookup.insert(std::make_pair('l', lTexture)); // Southwest lava
	m_textureLookup.insert(std::make_pair('v', vTexture)); // Inverted northeast lava
	m_textureLookup.insert(std::make_pair('u', uTexture)); // Inverted northwest lava
	m_textureLookup.insert(std::make_pair('m', mTexture)); // Inverted southeast lava
	m_textureLookup.insert(std::make_pair('h', hTexture)); // Inverted southwest lava
	m_textureLookup.insert(std::make_pair('=', equalsTexture)); // Stone floor
	m_textureLookup.insert(std::make_pair('q', qTexture)); // Door
	m_textureLookup.insert(std::make_pair('^', carrotTexture)); // Grass
	m_textureLookup.insert(std::make_pair('r', rTexture)); // North grass
	m_textureLookup.insert(std::make_pair('e', eTexture)); // Northeast grass
	m_textureLookup.insert(std::make_pair('f', fTexture)); // Northwest grass
	m_textureLookup.insert(std::make_pair('y', yTexture)); // Inverted northeast grass
	m_textureLookup.insert(std::make_pair('x', xTexture)); // Inverted northwest grass

	m_textureLookup.insert(std::make_pair('~',nullTexture)); // No texture yet/error texture
	// Manually add in restricted tiles here. These cant me moved on
	m_restrictedTiles.push_back('#');
	m_restrictedTiles.push_back('%');
	m_restrictedTiles.push_back('q');
	m_restrictedTiles.push_back('&');
	m_restrictedTiles.push_back('c');
	m_restrictedTiles.push_back('~');
	m_restrictedTiles.push_back('\n');

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
				case 't':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('t'));
					break;
				case 'c':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('c'));
					break;
				case '&':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('&'));
					break;
				case 'p':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('p'));
					break;
				case 'o':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('o'));
					break;
				case 'k':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('k'));
					break;
				case 'j':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('j'));
					break;
				case 'b':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('b'));
					break;
				case 'i':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('i'));
					break;
				case 'n':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('n'));
					break;
				case 'l':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('l'));
					break;
				case 'v':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('v'));
					break;
				case 'u':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('u'));
					break;
				case 'm':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('m'));
					break;
				case 'h':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('h'));
					break;
				case '=':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('='));
					break;
				case '^':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('^'));
					break;
				case 'r':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('r'));
					break;
				case 'e':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('e'));
					break;
				case 'f':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('f'));
					break;
				case 'y':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('y'));
					break;
				case 'x':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('x'));
					break;
				default:
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('~'));
					break;
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
				m_mapData[xPos][yPos] = 't';
				m_needsRender = true;
				m_renderer->require_static_redraw();
				return true;
			}
		}
	}
	return false;
}

void LevelManager::reset_map_data()
{
	m_mapData = m_originalMapData;
	m_needsRender = true;
	m_renderer->require_static_redraw();
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