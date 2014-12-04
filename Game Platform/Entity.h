#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Convert.h"
#include "EntityData.h"

class Entity : public Cell {
	public:
		Entity();
		virtual void Initialize(b2World& world, b2Vec2 position) {};
		virtual void Update() {};

		EntityData::entity_type GetType();
		void SetType(EntityData::entity_type type);

	protected:
		EntityData::entity_type type;	
};