#include <list>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "InputHandler.h"

class Movement {
	public:
		Movement() : SCALE(30.0f), TIMESTEP(1 / 60.0f), objects(std::list<Object>()) {};
		bool CreateGround(b2World& world, sf::Texture texture, b2Vec2 position);
		bool CreateBox(b2World& world, sf::Texture texture, b2Vec2 position);
		bool CreateCircle(b2World& world, sf::Texture texture, b2Vec2 position);
		bool MovementTest();

	private:
		const float SCALE;
		const float TIMESTEP;
		std::list<Object> objects;
};