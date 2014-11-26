#include "Box.h"

Box::Box() : Object() {
	shape = b2PolygonShape();
	type = ObjectData::object_type::IDLE;
}

void Box::Initialize(b2World& world, b2BodyType type, b2Vec2 position,
					 b2Vec2 size, float density, float friction) {
	bodyDef.position = position;
	bodyDef.type = type;
	body = world.CreateBody(&bodyDef);
	shape.SetAsBox((size.x / 2) / 30.0f, (size.y / 2) / 30.0f);
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);

	b2Fixture* objectSensorFixture = body->CreateFixture(&fixtureDef);
	ContactUserData* cud = new ContactUserData();
	if (type == b2_dynamicBody) {
		cud->type = ContactUserData::Type::ANIMATE;
	}
	else {
		cud->type = ContactUserData::Type::INANIMATE;
	}
	cud->data = this;
	objectSensorFixture->SetUserData(cud);
}