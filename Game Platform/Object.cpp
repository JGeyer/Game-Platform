#include "Object.h"

Object::Object(InputManager &inputManager) {
	isDead = false;
	size = b2Vec2_zero;
	bodyDef = b2BodyDef();
	fixtureDef = b2FixtureDef();
	this->inputManager = inputManager;
}

Object::~Object() {
	//body->GetWorld()->DestroyBody(body);
}

void Object::Initialize(b2World& world, b2BodyType type, b2Vec2 position,
						b2Vec2 size, float density, float friction) {
	bodyDef.position = position;
	this->size = size;
	bodyDef.type = type;
	body = world.CreateBody(&bodyDef);
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	body->CreateFixture(&fixtureDef);
}

void Object::LoadContent(sf::Texture texture, b2Vec2 origin) {
	this->texture = texture;
	this->origin = origin;
}

void Object::UnloadContent() {
	texture.~Texture();
}

void Object::Update(sf::Event event) {
	inputManager.Update(event);
	if (inputManager.KeyPressed(sf::Keyboard::Key::J)) {
		b2Vec2 vel = body->GetLinearVelocity();
		vel.y = -1.0f;
		body->SetAwake(true);
		body->SetLinearVelocity(vel);
	}
}

void Object::Draw(sf::RenderWindow &window) {
	sprite.setTexture(texture);
	sprite.setOrigin(origin.x, origin.y);
	sprite.setPosition(body->GetPosition().x * 30.0f,  body->GetPosition().y * 30.0f);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	window.draw(sprite);
}