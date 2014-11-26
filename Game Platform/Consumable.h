#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "ConsumableData.h"

class Consumable : public Cell {
	public:
		Consumable();
		virtual void Initialize(b2World& world, b2BodyType type, b2Vec2 position, 
								b2Vec2 size, float density, float friction);
		virtual void Update(sf::Event event);

		ConsumableData::consumable_type GetType();
		void SetType(ConsumableData::consumable_type type);

	protected:
		ConsumableData::consumable_type type;
};