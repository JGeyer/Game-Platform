#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Convert.h"
#include "InputManager.h"

class Player {
	public:
		Player(InputManager &inputManager);
		~Player();
		virtual void Initialize(b2World& world, b2Vec2 position);
		void LoadContent(sf::Texture texture, b2Vec2 origin);
		void UnloadContent();
		void Update(sf::Event event);
		void Draw(sf::RenderWindow &window);
		b2Body* body;

	protected:
		bool isDead;
		sf::Sprite sprite;
		sf::Texture texture;
		b2Vec2 origin;
		b2BodyDef bodyDef;
		b2PolygonShape shapeLeft;
		b2PolygonShape shapeRight;
		b2FixtureDef fixtureDef;

	private:
		InputManager inputManager;
};

#endif