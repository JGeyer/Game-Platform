#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "ObjectsInclude.h"
#include "ConsumablesInclude.h"
#include "EntitiesInclude.h"
#include "FileManager.h"
#include "MusicManager.h"
#include "TextureManager.h"

class CreationManager {
	public:
		static CreationManager &Instance();
		void LoadContent(char* lfFilename, b2World &world);
		void UnloadContent();

		std::string GetSong(std::string id);
		std::vector<Object*> GetObjects(b2World &world);
		std::vector<Consumable*> GetConsumables(b2World &world);
		std::vector<Entity*> GetEntities(b2World &world);
		
	private:
		CreationManager() : objectLibrary(), consumableLibrary(), entityLibrary() {};

		Object* CreateObject(b2World &world, std::vector<std::string> contents);
		Consumable* CreateConsumable(b2World &world, std::vector<std::string> contents);
		Entity* CreateEntity(b2World &world, std::vector<std::string> contents);

		std::vector<std::vector<std::string>> objectLibrary;
		std::vector<std::vector<std::string>> consumableLibrary;
		std::vector<std::vector<std::string>> entityLibrary;
};