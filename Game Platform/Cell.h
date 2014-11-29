#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "ContactUserData.h"

class Cell {
	public:
		Cell();
		~Cell();
		virtual void Initialize(b2World& world, b2BodyType type, b2Vec2 position, 
								b2Vec2 size, float density, float friction) {};
		void LoadContent(sf::Texture texture, b2Vec2 origin);
		void UnloadContent() {};
		virtual void Update(sf::Event event) {};
		void Draw(sf::RenderWindow &App);

		b2Body* GetBody();
		void SetIsDead(bool isDead);
		bool GetIsDead();

		enum Direction { NONE, LEFT, RIGHT, UP, DOWN } direction;

	protected:
		b2Body* body;
		bool isDead;
		b2Vec2 size;
		b2Vec2 origin;
		b2BodyDef bodyDef;
		b2FixtureDef fixtureDef;
		sf::Sprite sprite;
		sf::Texture texture;
};