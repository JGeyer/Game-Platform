#include "Circle.h"

Circle::Circle(InputManager &inputManager) : Object(inputManager) {
	shape = b2CircleShape();
}

Circle::~Circle() {
	Object::~Object();
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
}