#include "Consumable.h"

Consumable::Consumable() : Cell() {
	type = ConsumableData::consumable_type::NONE;
}

void Consumable::Initialize(b2World& world, b2BodyType type, b2Vec2 position,
							b2Vec2 size, float density, float friction) {
	//OVERRIDE ME
}

void Consumable::Update(sf::Event event) {
	//OVERRIDE ME
}

ConsumableData::consumable_type Consumable::GetType() {
	return type;
}

void Consumable::SetType(ConsumableData::consumable_type type) {
	this->type = type;
}