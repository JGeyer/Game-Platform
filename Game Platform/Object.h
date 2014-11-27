#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "ObjectData.h"

class Object : public Cell {
	public:
		Object();
		virtual void Initialize(b2World& world, b2BodyType type, b2Vec2 position, 
								b2Vec2 size, float density, float friction) {};

		ObjectData::object_type GetType();
		void SetType(ObjectData::object_type type);

	protected:
		ObjectData::object_type type;
};