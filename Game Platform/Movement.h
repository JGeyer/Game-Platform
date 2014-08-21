#include <vector>
#include "FileManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"

class Movement {
	public:
		Movement() : SCALE(30.0f), TIMESTEP(1 / 60.0f), objects(std::vector<Object>()), inputManager() {};
		//Object CreateCircle(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position);
		Player CreatePlayer(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position);
		bool MovementTest();

	private:
		const float SCALE;
		const float TIMESTEP;
		std::vector<Object> objects;
		InputManager inputManager;
};