#include "TextureCache.h"
#include "picoPNG.h"
#include <iostream>
#include <fstream>
#include <windows.h>

TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{
	for (auto& it : m_textureCache) {
		glDeleteTextures(1, &it.second.textureID);
	}
}

GLuint TextureCache::get_texture_id(std::string texturePath)
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	std::string projectDirectory = std::string(buf) + '\\';
	projectDirectory += "Resources\\Textures\\";
	size_t found = texturePath.find_last_of("/") + 1;
	std::string textureName = texturePath.substr(found);

	std::unordered_map<std::string, Texture>::iterator it;
	it = m_textureCache.find(textureName);
	// If true has not found the texture and will add it
	if (it == m_textureCache.end())
	{
		Texture newTexture;
		load_texture_from_PNG(projectDirectory + texturePath, newTexture.textureID);
		//new_texture.name = texturePath;

		m_textureCache.insert(std::make_pair(texturePath, newTexture));
		return newTexture.textureID;
	}
	return it->second.textureID;
}

bool TextureCache::load_texture_from_PNG(std::string texturePath, GLuint& textureID)
{
	std::vector <unsigned char> inImage;
	std::vector <unsigned char> outImage;
	unsigned long width, height;

	std::ifstream file(texturePath, std::ios::binary | std::ios::in);

	if (file.fail()) {
		perror(texturePath.c_str());
		return false;
	}
	file.seekg(0, std::ios::end);
	// Get the size of the file
	int fileSize = file.tellg();
	// Seek back to beginning
	file.seekg(0, std::ios::beg);
	// Make sure we dont count the file header in the file size
	fileSize -= file.tellg();
	// Resize the given buffer to the filesize
	inImage.resize(fileSize);
	file.read((char*)&(inImage[0]), fileSize);

	file.close();



	int errorCode = decodePNG(outImage, width, height, &(inImage[0]), inImage.size());
	if (errorCode != 0) {
		std::cout << "decodePNG failed." << std::endl;
	}



	glGenTextures(1, &(textureID));
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(outImage[0]));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);




}

