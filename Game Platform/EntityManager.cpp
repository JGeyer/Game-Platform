#include "EntityManager.h"

EntityManager &EntityManager::Instance() {
	static EntityManager instance;
	return instance;
}

void EntityManager::LoadContent(std::vector<std::vector<std::string>> objects) {
	for (int i = 0; i < objects.size(); i++) {
		entityLibrary.insert(std::pair<std::string, std::vector<std::string>>(objects[i][0], objects[i]));
	}
}

void EntityManager::UnloadContent() {
	entityLibrary.clear();
}

Entity* EntityManager::createEntity(b2World &world, std::string id, sf::Texture texture) {
	std::vector<std::string> contents = entityLibrary.find(id)->second;
	if (contents[1].compare("player") == 0) {
		Player* player = new Player();
		player->Initialize(world, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f));
		player->LoadContent(texture, b2Vec2(std::stof(contents[4]), std::stof(contents[5])));
		return player;
	}
	if (contents[1].compare("grunt") == 0) {
		Enemy* enemy = new Enemy(EnemyData::enemy_type::GRUNT, EnemyData::enemy_rank::REGULAR);
		enemy->Initialize(world, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f));
		enemy->LoadContent(texture, b2Vec2(std::stof(contents[4]), std::stof(contents[5])));
		return enemy;
	}
	//TODO: Proper handle here
	return NULL;
}