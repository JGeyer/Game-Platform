#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Consumable.h"
#include "MaterialData.h"

class Material : public Consumable {
	public:
		Material();

		MaterialData::material_type mat_type;

		void Initialize(b2World& world, b2BodyType type, b2Vec2 position, b2Vec2 size, MaterialData::material_type mat_type);

	private:
		b2PolygonShape shape;

};