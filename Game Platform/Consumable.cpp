#include "Consumable.h"

Consumable::Consumable() : Cell() {
	type = ConsumableData::consumable_type::NONE;
}

ConsumableData::consumable_type Consumable::GetType() {
	return type;
}

void Consumable::SetType(ConsumableData::consumable_type type) {
	this->type = type;
}