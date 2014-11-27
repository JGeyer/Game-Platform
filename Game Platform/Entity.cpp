#include "Entity.h"

Entity::Entity() : Cell() {
	type = EntityData::entity_type::NONE;
	direction = Entity::Direction::NONE;
}

EntityData::entity_type Entity::GetType() {
	return type;
}

void Entity::SetType(EntityData::entity_type type) {
	this->type = type;
}