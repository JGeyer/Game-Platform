#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Box.h"
#include "Circle.h"
#include "Player.h"

class ObjectManager {
	public:
		static ObjectManager &Instance();
		void setObjectLibrary(std::vector<std::vector<std::string>> textures);
		void clearObjectLibrary();
		Object createObject(InputManager inputManager, b2World &world, std::string id, sf::Texture texture);
		std::vector<Object> createObjects(InputManager inputManager, b2World &world, std::vector<std::string>, sf::Texture texture);
		std::vector<Object> getObjects();

	private:
		ObjectManager() : objectLibrary() {};
		std::map<std::string, std::vector<std::string>> objectLibrary;
};