#include "Box.h"

Box::Box(InputManager &inputManager) : Object(inputManager) {
	shape = b2PolygonShape();
}

Box::~Box() {
	Object::~Object();
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
}