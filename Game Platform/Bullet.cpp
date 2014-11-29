#include "Bullet.h"

Bullet::Bullet() : Object() {
	shape = b2PolygonShape();
	type = ObjectData::object_type::BULLET;
	direction = Cell::Direction::NONE;
	speed = 20.0f;
	damage = 10;
}

void Bullet::Initialize(b2World& world, b2Vec2 position, Cell::Direction direction, float speed, int damage) {
	bodyDef.position = position;
	bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&bodyDef);
	shape.SetAsBox(5.0f / 30.0f, 5.0f/ 30.0f);
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
	this->direction = direction;
	this->speed = speed;
	this->damage = damage;

	b2Fixture* bulletSensorFixture = body->CreateFixture(&fixtureDef);
	ContactUserData* cud = new ContactUserData();
	cud->type = ContactUserData::Type::BULLET;
	cud->data = this;
	bulletSensorFixture->SetUserData(cud);
}

void Bullet::Update(sf::Event event) {
	float mass = body->GetMass();
	b2Vec2 vel = body->GetLinearVelocity();
	if (direction == Cell::Direction::LEFT) {
		body->SetLinearVelocity(b2Vec2(-speed, -0.7f));
	}
	if (direction == Cell::Direction::RIGHT) {
		body->SetLinearVelocity(b2Vec2(speed, -0.7f));
	}
	body->SetAwake(true);
}

int Bullet::GetDamage() {
	return damage;
}