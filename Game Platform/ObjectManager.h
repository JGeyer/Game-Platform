#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "ObjectsInclude.h"

class ObjectManager {
	public:
		static ObjectManager &Instance();
		void LoadContent(std::vector<std::vector<std::string>> textures);
		void UnloadContent();
		Object* createObject(b2World &world, std::string id, sf::Texture texture);

	private:
		ObjectManager() : objectLibrary() {};
		std::map<std::string, std::vector<std::string>> objectLibrary;
};