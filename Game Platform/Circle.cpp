#include "Circle.h"

Circle::Circle() : Object() {
	shape = b2CircleShape();
	type = ObjectData::object_type::IDLE;
}

void Circle::Initialize(b2World& world, b2BodyType type, b2Vec2 position,
						float radius, float density, float friction) {
	bodyDef.position = position;
	bodyDef.type = type;
	body = world.CreateBody(&bodyDef);
	shape.m_radius = radius;
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