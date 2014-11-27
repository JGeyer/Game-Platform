#include "Cell.h"

Cell::Cell() {
	body = NULL;
	isDead = false;
	size = b2Vec2_zero;
	bodyDef = b2BodyDef();
	fixtureDef = b2FixtureDef();
}

Cell::~Cell() {
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
		delete f->GetUserData();
	}
	body->GetWorld()->DestroyBody(body);
}

void Cell::LoadContent(sf::Texture texture, b2Vec2 origin) {
	this->texture = texture;
	this->origin = origin;
}

void Cell::Draw(sf::RenderWindow &window) {
	sprite.setTexture(texture);
	sprite.setOrigin(origin.x, origin.y);
	sprite.setPosition(body->GetPosition().x * 30.0f,  body->GetPosition().y * 30.0f);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	window.draw(sprite);
}

b2Body* Cell::GetBody() {
	return body;
}

void Cell::SetIsDead(bool isDead) {
	this->isDead = isDead;
}

bool Cell::GetIsDead() {
	return isDead;
}