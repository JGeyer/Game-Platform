#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "ConsumableManager.h"
#include "EntityManager.h"
#include "FileManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"

class LevelManager {
	public:
		static LevelManager &Instance();
		void LoadContent(char* lfFilename, b2World &world, FileManager* fileManager);
		void UnloadContent();

		std::vector<Object*> getObjects();
		std::vector<Consumable*> getConsumables();
		std::vector<Entity*> getEntities();

	private:
		LevelManager() : lfFilename(""), levelObjects(), levelConsumables(), levelEntities() {};
		char* lfFilename;
		std::vector<Object*> levelObjects;
		std::vector<Consumable*> levelConsumables;
		std::vector<Entity*> levelEntities;
};