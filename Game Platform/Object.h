#include <Box2D/Box2D.h>

#include "WindowHandler.h"

const float SCALE = 30.0f;

struct Object {
	bool IsDead;
	sf::Sprite Sprite;
	sf::Texture Texture;
	b2Vec2 Origin;
	b2BodyDef BodyDef;
	b2Body* Body;
	b2FixtureDef FixtureDef;
	void UpdateSprite() {
		Sprite.setTexture(Texture);
		Sprite.setOrigin(Origin.x, Origin.y);
		Sprite.setPosition(Body->GetPosition().x * SCALE,  Body->GetPosition().y * SCALE);
		Sprite.setRotation(Body->GetAngle() * 180 / b2_pi);
	}
	void DrawSprite() {
		WindowHandler::Instance().draw(Sprite);
	}
};

struct Box : public Object {
	b2PolygonShape Shape;

	Box(b2World& world, sf::Texture texture, b2Vec2 origin, b2BodyType type, b2Vec2 position,
			b2Vec2 size, float density, float friction) {
		IsDead = false;
		Texture = texture;
		Origin = origin;
		BodyDef.position = position;
		BodyDef.type = type;
		Body = world.CreateBody(&BodyDef);
		Shape.SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
		FixtureDef.density = density;
		FixtureDef.friction = friction;
		FixtureDef.shape = &Shape;
		Body->CreateFixture(&FixtureDef);
	}
};

struct Circle : public Object {
	b2CircleShape Shape;

	Circle(b2World& world, sf::Texture texture, b2Vec2 origin, b2BodyType type, b2Vec2 position,
			float radius, float density, float friction) {
		IsDead = false;
		Texture = texture;
		Origin = origin;
		BodyDef.position = position;
		BodyDef.type = type;
		Body = world.CreateBody(&BodyDef);
		Shape.m_radius = radius;
		FixtureDef.density = density;
		FixtureDef.friction = friction;
		FixtureDef.shape = &Shape;
		Body->CreateFixture(&FixtureDef);
	}
};