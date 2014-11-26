#include "ConsumableManager.h"

ConsumableManager &ConsumableManager::Instance() {
	static ConsumableManager instance;
	return instance;
}

void ConsumableManager::LoadContent(std::vector<std::vector<std::string>> objects) {
	for (int i = 0; i < objects.size(); i++) {
		consumableLibrary.insert(std::pair<std::string, std::vector<std::string>>(objects[i][0], objects[i]));
	}
}

void ConsumableManager::UnloadContent() {
	consumableLibrary.clear();
}

Consumable* ConsumableManager::createConsumable(b2World &world, std::string id, sf::Texture texture) {
	std::vector<std::string> contents = consumableLibrary.find(id)->second;
	if (contents[1].compare("material") == 0) {
		Material* material = new Material();
		b2BodyType type;
		if (contents[11].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[11].compare("dynamic") == 0
			type = b2_dynamicBody;
		}
		MaterialData::material_type mat_type;
		if (contents[10].compare("copper") == 0) {
			mat_type = MaterialData::material_type::COPPER;
		}
		if (contents[10].compare("iron") == 0) {
			mat_type = MaterialData::material_type::IRON;
		}
		if (contents[10].compare("carbon") == 0) {
			mat_type = MaterialData::material_type::CARBON;
		}
		if (contents[10].compare("zinc") == 0) {
			mat_type = MaterialData::material_type::ZINC;
		}
		material->Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f), 
							 b2Vec2(std::stof(contents[4]), std::stof(contents[5])), std::stof(contents[8]),
							 std::stof(contents[9]), mat_type);
		material->LoadContent(texture, b2Vec2(std::stof(contents[6]), std::stof(contents[7])));
		return material;
	}
	//TODO: Proper handle here
	return NULL;
}