#pragma once

#include "Object.h"

class Circle : public Object {
	public:
		Circle();

		void Initialize(b2World& world, b2BodyType type, b2Vec2 position, 
						float radius, float density, float friction);

	protected:
		b2CircleShape shape;
};