#include "LevelManager.h"
#include <fstream>


LevelManager::LevelManager() {
	// Empty
}

void LevelManager::init(const std::string& projectDirectory, SpriteRenderer& renderer) {
	m_renderer = &renderer;
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

	char c;

}

void LevelManager::render() {
	// Verify that the renderer has been properly initialized with a non-nullptr value
	if (m_renderer == nullptr) {
		return;
	}

	// Go through the 2D vector and render each tile. 
	// Go of the logic that a tile in location of 0 0 (in the vector)
	// should be rendered at position x=0, y=0.
	// If 2D vector position is at 5 7, the position would be at
	// x = 5 * (width of tile) and y = 7 * (height of tile)
	// The offset variables account for the size of each tile to correctly
	// align the tile.
	for (size_t x = 0; x < m_mapData.size(); x++) {
		for (size_t y = 0; y < m_mapData[x].size(); y++) {
			float xOffset = (float)x * m_tileSize.x;
			float yOffset = (float)y * m_tileSize.y;
			glm::vec2 tileCenter = glm::vec2(xOffset, yOffset);
			
			// Determine what the current character is and render its associated texture
			switch (m_mapData[x][y]) {
			case '#':
				m_renderer->add_sprite_to_batch(tileCenter, m_tileSize, "dark_crate_five.PNG", 0.0f);
				break;
			case '-':
				m_renderer->add_sprite_to_batch(tileCenter, m_tileSize, "grass.PNG", 0.0f);
				break;

			default:
				break;
				// Maybe add a texture showing ERROR
			}
		}
	}
}

void LevelManager::update() {

}