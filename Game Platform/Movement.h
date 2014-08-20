#include "InputManager.h"
#include "Box.h"
#include "Circle.h"
#include <list>

class Movement {
	public:
		Movement() : SCALE(30.0f), TIMESTEP(1 / 60.0f), objects(std::list<Object>()), inputManager() {};
		Object CreateGround(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position);
		Object CreateBox(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position);
		Object CreateCircle(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position);
		Object CreateCharacter(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position);
		bool MovementTest();

	private:
		const float SCALE;
		const float TIMESTEP;
		std::list<Object> objects;
		InputManager inputManager;

};