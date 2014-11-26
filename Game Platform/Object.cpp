#include "Object.h"

Object::Object() : Cell() {
	type = ObjectData::object_type::NONE;
}

void Object::Initialize(b2World& world, b2BodyType type, b2Vec2 position,
						b2Vec2 size, float density, float friction) {

}

ObjectData::object_type Object::GetType() {
	return type;
}

void Object::SetType(ObjectData::object_type type) {
	this->type = type;
}