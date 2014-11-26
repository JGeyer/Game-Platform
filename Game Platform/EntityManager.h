#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "EntitiesInclude.h"

class EntityManager {
	public:
		static EntityManager &Instance();
		void LoadContent(std::vector<std::vector<std::string>> textures);
		void UnloadContent();
		Entity* createEntity(b2World &world, std::string id, sf::Texture texture);

	private:
		EntityManager() : entityLibrary() {};
		std::map<std::string, std::vector<std::string>> entityLibrary;
};