#include "Object.h"

Object::Object() : Cell() {
	type = ObjectData::object_type::NONE;
}

ObjectData::object_type Object::GetType() {
	return type;
}

void Object::SetType(ObjectData::object_type type) {
	this->type = type;
}