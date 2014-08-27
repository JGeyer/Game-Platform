#include <vector>
#include "ContactListener.h"
#include "InputManager.h"
#include "LevelManager.h"

class Movement {
	public:
		Movement() : SCALE(30.0f), TIMESTEP(1 / 60.0f), objects(std::vector<Object>()), inputManager(), contactListener(new ContactListener()) {};
		//Object CreateCircle(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position);
		Player CreatePlayer(InputManager inputManager, ContactListener *contactListener, b2World& world, sf::Texture texture, b2Vec2 position);
		bool MovementTest();

	private:
		const float SCALE;
		const float TIMESTEP;
		std::vector<Object> objects;
		FileManager fileManager;
		InputManager inputManager;
		ContactListener* contactListener;
};