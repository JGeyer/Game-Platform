#include "TextureManager.h"

TextureManager &TextureManager::Instance() {
	static TextureManager instance;
	return instance;
}

void TextureManager::setTextureLibrary(std::string path, std::vector<std::vector<std::string>> textures) {
	for (int i = 0; i < textures.size(); i++) {
		textureLibrary.insert(std::pair<std::string, std::string>(textures[i][0], path + textures[i][1]));
	}
	for (std::map<std::string, std::string>::iterator itt = textureLibrary.begin(); itt != textureLibrary.end(); itt++) {
		std::cout << textureLibrary[itt->first] << std::endl;
	}
}

void TextureManager::clearTextureLibrary() {
	textureLibrary.clear();
}

sf::Texture TextureManager::getTexture(std::string id) {
	std::string filepath = textureLibrary.find(id)->second;
	sf::Texture texture;
	texture.loadFromFile(filepath);
	return texture;
}