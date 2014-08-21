#include "ObjectManager.h"

ObjectManager &ObjectManager::Instance() {
	static ObjectManager instance;
	return instance;
}

void ObjectManager::setObjectLibrary(std::vector<std::vector<std::string>> objects) {
	for (int i = 0; i < objects.size(); i++) {
		objectLibrary.insert(std::pair<std::string, std::vector<std::string>>(objects[i][0], objects[i]));
	}
	for (std::map<std::string, std::vector<std::string>>::iterator itt = objectLibrary.begin(); itt != objectLibrary.end(); itt++) {
		//std::cout << bodyLibrary[itt->first] << std::endl;
	}
}

Object ObjectManager::createObject(InputManager inputManager, b2World &world, std::string id, sf::Texture texture) {
	std::vector<std::string> contents = objectLibrary.find(id)->second;
	if (contents[1].compare("box") == 0) {
		Box box = Box(inputManager);
		b2BodyType type;
		if (contents[10].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[10].compare("dynamic") == 0
			type = b2_dynamicBody;
		}
		box.Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f), 
					   b2Vec2(std::stof(contents[4]), std::stof(contents[5])), std::stof(contents[8]), std::stof(contents[9]));
		box.LoadContent(texture, b2Vec2(std::stof(contents[6]), std::stof(contents[7])));
		return box;
	}
	else if (contents[1].compare("circle") == 0) {
		Circle circle = Circle(inputManager);
		b2BodyType type;
		if (contents[9].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[9].compare("dynamic") == 0
			type = b2_dynamicBody;
		}
		circle.Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f),
						  std::stof(contents[4]), std::stof(contents[7]), std::stof(contents[8]));
		circle.LoadContent(texture, b2Vec2(std::stof(contents[5]), std::stof(contents[6])));
		return circle;
	}
	else {
		// Error, do nothing
	}
}

std::vector<Object> ObjectManager::createObjects(InputManager inputManager, b2World &world, std::vector<std::string> ids, sf::Texture texture) {
	std::vector<Object> objects;
	for (std::vector<std::string>::iterator it = ids.begin(); it != ids.end(); it++) {
		objects.push_back(createObject(inputManager, world, *it, texture));
	}
	return objects;
}