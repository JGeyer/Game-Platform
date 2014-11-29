#pragma once

#include "Object.h"

class Bullet : public Object {
	public:
		Bullet();
		void Initialize(b2World& world, b2Vec2 position, Cell::Direction direction, float speed, int damage);
		void Update(sf::Event event);
	
		int GetDamage();

	protected:
		b2PolygonShape shape;
		Cell::Direction direction;
		float speed;
		int damage;
};