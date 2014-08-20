#ifndef OBJECT_H
#define OBJECT_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "InputManager.h"

class Object {
	public:
		Object(InputManager &inputManager);
		~Object();
		virtual void Initialize(b2World& world, b2BodyType type, b2Vec2 position, 
								b2Vec2 size, float density, float friction);
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
		b2FixtureDef fixtureDef;

	private:
		InputManager inputManager;
};

#endif