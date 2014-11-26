#include "Entity.h"

Entity::Entity() : Cell() {
	type = EntityData::entity_type::NONE;
}

void Entity::Initialize(b2World& world, b2Vec2 position) {
	//OVERRIDE ME
}

void Entity::Update(sf::Event event) {
	//OVERRIDE ME
}

void Entity::UpdatePassive() {
	//OVERRIDE ME
}

EntityData::entity_type Entity::GetType() {
	return type;
}

void Entity::SetType(EntityData::entity_type type) {
	this->type = type;
}