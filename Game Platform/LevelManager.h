#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "FileManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"

class LevelManager {
	public:
		static LevelManager &Instance();
		std::vector<Object> LoadContent(char* lfFilename, b2World &world, FileManager fileManager, InputManager inputManager);
		void UnloadContent();

	private:
		LevelManager() : lfFilename(""), levelObjects() {};
		char* lfFilename;
		std::vector<Object> levelObjects;
};