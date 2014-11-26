#pragma once

#include "Object.h"

class Box : public Object {
	public:
		Box();

		virtual void Initialize(b2World& world, b2BodyType type, b2Vec2 position, 
							    b2Vec2 size, float density, float friction);

	protected:
		b2PolygonShape shape;
};