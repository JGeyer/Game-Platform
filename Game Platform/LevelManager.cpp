#include "LevelManager.h"
#include <iostream>

LevelManager &LevelManager::Instance() {
	static LevelManager instance;
	return instance;
}

std::vector<Object> LevelManager::LoadContent(char* lfFilename, b2World &world, FileManager fileManager, InputManager inputManager) {
	this->lfFilename = lfFilename;
	//std::cout << lfFilename << std::endl;
	std::vector<std::vector<std::string>> attributes, contents, pairings, textures, objects;
	std::string path;

	fileManager.LoadContent(lfFilename, attributes, contents);
	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i][0] == "path") {
			path = contents[i][0];
		}
		if (attributes[i][0] == "texture") {
			textures.push_back(contents[i]);
		}
		if (attributes[i][0] == "object") {
			objects.push_back(contents[i]);
		}
		if (attributes[i][0] == "level") {
			pairings.push_back(contents[i]);
		}
	}
	TextureManager::Instance().setTextureLibrary(path, textures);
	ObjectManager::Instance().setObjectLibrary(objects);

	for (int i = 0; i < pairings.size(); i++) {
		sf::Texture currentTexture = TextureManager::Instance().getTexture(pairings[i][1]);
		levelObjects.push_back(ObjectManager::Instance().createObject(inputManager, world, pairings[i][0], currentTexture));
	}
	return levelObjects;
}

void LevelManager::UnloadContent() {
	lfFilename = "";
	levelObjects.clear();
}