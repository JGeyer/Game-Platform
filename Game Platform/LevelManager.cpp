#include "LevelManager.h"

LevelManager &LevelManager::Instance() {
	static LevelManager instance;
	return instance;
}

void LevelManager::LoadContent(char* lfFilename, b2World &world, FileManager* fileManager) {
	this->lfFilename = lfFilename;
	std::vector<std::vector<std::string>> attributes, contents, textures, objects, consumables, entities;
	std::string path;

	// Load Attributes and Contents
	fileManager->LoadContent(lfFilename, attributes, contents);
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
		if (attributes[i][0] == "consumable") {
			consumables.push_back(contents[i]);
		}
		if (attributes[i][0] == "entity") {
			entities.push_back(contents[i]);
		}
	}

	// Reset Previous  Libraries
	TextureManager::Instance().UnloadContent();
	ObjectManager::Instance().UnloadContent();
	ConsumableManager::Instance().UnloadContent();
	EntityManager::Instance().UnloadContent();

	// Setup new  Libraries
	TextureManager::Instance().LoadContent(path, textures);	
	ObjectManager::Instance().LoadContent(objects);
	ConsumableManager::Instance().LoadContent(consumables);
	EntityManager::Instance().LoadContent(entities);

	// For each texture-object pair, pull the correct texture from the library, create the corresponding object
	// with correct texture and add to the level objects vector, then return the finished vector with all
	// appropriate texture-object pairings
	sf::Texture currentTexture;
	for (int i = 0; i < objects.size(); i++) {
		currentTexture = TextureManager::Instance().getTexture(objects[i][11]);
		levelObjects.push_back(ObjectManager::Instance().createObject(world, objects[i][0], currentTexture));
	}
	for (int i = 0; i < consumables.size(); i++) {
		currentTexture = TextureManager::Instance().getTexture(consumables[i][12]);
		levelConsumables.push_back(ConsumableManager::Instance().createConsumable(world, consumables[i][0], currentTexture));
	}
	for (int i = 0; i < entities.size(); i++) {
		currentTexture = TextureManager::Instance().getTexture(entities[i][6]);
		levelEntities.push_back(EntityManager::Instance().createEntity(world, entities[i][0], currentTexture));
	}
}

void LevelManager::UnloadContent() {
	lfFilename = "";
	levelObjects.clear();
	levelConsumables.clear();
	levelEntities.clear();
}

std::vector<Object*> LevelManager::getObjects() {
	return levelObjects;
}

std::vector<Consumable*> LevelManager::getConsumables() {
	return levelConsumables;
}

std::vector<Entity*> LevelManager::getEntities() {
	return levelEntities;
}