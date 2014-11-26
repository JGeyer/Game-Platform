#include "ObjectManager.h"

ObjectManager &ObjectManager::Instance() {
	static ObjectManager instance;
	return instance;
}

void ObjectManager::LoadContent(std::vector<std::vector<std::string>> objects) {
	for (int i = 0; i < objects.size(); i++) {
		objectLibrary.insert(std::pair<std::string, std::vector<std::string>>(objects[i][0], objects[i]));
	}
}

void ObjectManager::UnloadContent() {
	objectLibrary.clear();
}

Object* ObjectManager::createObject(b2World &world, std::string id, sf::Texture texture) {
	std::vector<std::string> contents = objectLibrary.find(id)->second;
	if (contents[1].compare("box") == 0) {
		Box* box = new Box();
		b2BodyType type;
		if (contents[10].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[10].compare("dynamic") == 0
			type = b2_dynamicBody;
		}
		box->Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f), 
					   b2Vec2(std::stof(contents[4]), std::stof(contents[5])), std::stof(contents[8]), std::stof(contents[9]));
		box->LoadContent(texture, b2Vec2(std::stof(contents[6]), std::stof(contents[7])));
		return box;
	}
	if (contents[1].compare("circle") == 0) {
		Circle* circle = new Circle();
		b2BodyType type;
		if (contents[9].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[9].compare("dynamic") == 0
			type = b2_dynamicBody;
		}
		circle->Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f),
						  std::stof(contents[4]), std::stof(contents[7]), std::stof(contents[8]));
		circle->LoadContent(texture, b2Vec2(std::stof(contents[5]), std::stof(contents[6])));
		return circle;
	}
	//TODO: Proper handle here
	return NULL;
}