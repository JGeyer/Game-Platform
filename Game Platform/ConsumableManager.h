#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "ConsumablesInclude.h"

class ConsumableManager {
	public:
		static ConsumableManager &Instance();
		void LoadContent(std::vector<std::vector<std::string>> textures);
		void UnloadContent();
		Consumable* createConsumable(b2World &world, std::string id, sf::Texture texture);

	private:
		ConsumableManager() : consumableLibrary() {};
		std::map<std::string, std::vector<std::string>> consumableLibrary;
};