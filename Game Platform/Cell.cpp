#include "Cell.h"

Cell::Cell() {
	isDead = false;
	size = b2Vec2_zero;
	bodyDef = b2BodyDef();
	fixtureDef = b2FixtureDef();
}

Cell::~Cell() {
	body->GetWorld()->DestroyBody(body);
}

void Cell::Initialize(b2World& world, b2BodyType type, b2Vec2 position,
					  b2Vec2 size, float density, float friction) {
	//OVERRIDE ME
}

void Cell::LoadContent(sf::Texture texture, b2Vec2 origin) {
	this->texture = texture;
	this->origin = origin;
}

void Cell::UnloadContent() {
	texture.~Texture();
}

void Cell::Update(sf::Event event) {
	//OVERRIDE ME
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