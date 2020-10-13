#include "LevelManager.h"
#include <fstream>


LevelManager::LevelManager() {

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
	m_map.push_back(std::vector<char>());
	for (size_t i = 0; i < mapData.size(); i++) {
		if (mapData[i] == '\n') {
			row += 1;
			m_map.push_back(std::vector<char>());
		}
		m_map[row].push_back(mapData[i]);
	}

	char c;

}

void LevelManager::render() {
	if (m_renderer == nullptr) {
		return;
	}
	for (size_t x = 0; x < m_map.size(); x++) {
		for (size_t y = 0; y < m_map[x].size(); y++) {
			float xOffset = (float)x * (tileSize.x);
			float yOffset = (float)y * (tileSize.y);
			glm::vec2 tileCenter = glm::vec2(xOffset, yOffset);


			switch (m_map[x][y]) {
			case '#':
				m_renderer->add_sprite_to_batch(tileCenter, tileSize, "dark_crate_five.PNG", 0.0f);
				break;

			case '-':
				m_renderer->add_sprite_to_batch(tileCenter, tileSize, "grass.PNG", 0.0f);
				break;
			}
		}
	}
}

void LevelManager::update() {

}