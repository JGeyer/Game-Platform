#include "Player.h"

Player::Player(InputManager &inputManager, ContactListener *contactListener) {
	isDead = false;
	bodyDef = b2BodyDef();
	shapeLeft = b2PolygonShape();
	shapeRight = b2PolygonShape();
	fixtureDef = b2FixtureDef();
	this->inputManager = inputManager;
	this->contactListener = contactListener;
	c= 0;
}

Player::~Player() {
	//body->GetWorld()->DestroyBody(body);
}

void Player::Initialize(b2World& world, b2Vec2 position) {
	bodyDef.position = position;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	body = world.CreateBody(&bodyDef);

	Convert convert;
	b2Vec2 vs0, vs1, vs2, vs3, vs4, vs5;

	b2Vec2* vsLeft = new b2Vec2[6];
	vs0 = convert.CoordPixelsToWorld(0, 80, 80.0f, 80.0f);
	vs1 = convert.CoordPixelsToWorld(5, 49, 80.0f, 80.0f);
	vs2 = convert.CoordPixelsToWorld(17, 22, 80.0f, 80.0f);
	vs3 = convert.CoordPixelsToWorld(28, 10, 80.0f, 80.0f);
	vs4 = convert.CoordPixelsToWorld(40, 7, 80.0f, 80.0f);
	vs5 = convert.CoordPixelsToWorld(40, 80, 80.0f, 80.0f);
	vsLeft[0].Set(vs0.x, vs0.y);
	vsLeft[1].Set(vs1.x, vs1.y);
	vsLeft[2].Set(vs2.x, vs2.y);
	vsLeft[3].Set(vs3.x, vs3.y);
	vsLeft[4].Set(vs4.x, vs4.y);
	vsLeft[5].Set(vs5.x, vs5.y);
	shapeLeft.Set(vsLeft, 6);

	b2Vec2* vsRight = new b2Vec2[6];
	vs0 = convert.CoordPixelsToWorld(40, 7, 80.0f, 80.0f);
	vs1 = convert.CoordPixelsToWorld(46, 9, 80.0f, 80.0f);
	vs2 = convert.CoordPixelsToWorld(63, 26, 80.0f, 80.0f);
	vs3 = convert.CoordPixelsToWorld(71, 46, 80.0f, 80.0f);
	vs4 = convert.CoordPixelsToWorld(80, 80, 80.0f, 80.0f);
	vs5 = convert.CoordPixelsToWorld(40, 80, 80.0f, 80.0f);
	vsRight[0].Set(vs0.x, vs0.y);
	vsRight[1].Set(vs1.x, vs1.y);
	vsRight[2].Set(vs2.x, vs2.y);
	vsRight[3].Set(vs3.x, vs3.y);
	vsRight[4].Set(vs4.x, vs4.y);
	vsRight[5].Set(vs5.x, vs5.y);
	shapeRight.Set(vsRight, 6);

	b2PolygonShape footSensor;
	footSensor.SetAsBox(0.033f * 30.0f, 0.033f * 3.0f, b2Vec2(0, 1.33f), 0);
	b2FixtureDef footFixtureDef;
	footFixtureDef.density = 1;
	footFixtureDef.shape = &footSensor;
	footFixtureDef.isSensor = true;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.shape = &shapeLeft;
	body->CreateFixture(&fixtureDef);
	fixtureDef.shape = &shapeRight;
	body->CreateFixture(&fixtureDef);
	b2Fixture* footSensorFixture = body->CreateFixture(&footFixtureDef);
	footSensorFixture->SetUserData((void*)3);
}

void Player::LoadContent(sf::Texture texture, b2Vec2 origin) {
	this->texture = texture;
	this->origin = origin;
}

void Player::UnloadContent() {
	texture.~Texture();
}

#include <iostream>

void Player::Update(sf::Event event) {
	inputManager.Update(event);
	int numFootContacts = contactListener->numFootContacts;

	std::vector<sf::Keyboard::Key> movementKeys;
	movementKeys.push_back(sf::Keyboard::Key::Left);
	movementKeys.push_back(sf::Keyboard::Key::Right);
	movementKeys.push_back(sf::Keyboard::Key::Space);
	if (inputManager.KeyPressed(movementKeys) || inputManager.KeyDown(movementKeys)) {
		if (inputManager.KeyPressed(sf::Keyboard::Key::Space) || inputManager.KeyDown(sf::Keyboard::Key::Space)) {
			if (numFootContacts > 0) {
				body->ApplyLinearImpulse(b2Vec2(0, -(body->GetMass() * 5)), body->GetWorldCenter(), true);
			}
		}
		if (inputManager.KeyPressed(sf::Keyboard::Key::Left) || inputManager.KeyDown(sf::Keyboard::Key::Left)) {
			sprite.setScale(-1, 1);
			b2Vec2 vel = body->GetLinearVelocity();
			vel.x = -4.0f;
			body->SetAwake(true);
			body->SetLinearVelocity(vel);
			c++;
			std::cout << c << std::endl;
		}
		if (inputManager.KeyPressed(sf::Keyboard::Key::Right) || inputManager.KeyDown(sf::Keyboard::Key::Right)) {
			sprite.setScale(1, 1);
			b2Vec2 vel = body->GetLinearVelocity();
			vel.x = 4.0f;
			body->SetAwake(true);
			body->SetLinearVelocity(vel);
		}
	}
}

void Player::Draw(sf::RenderWindow &window) {
	sprite.setTexture(texture);
	sprite.setOrigin(origin.x, origin.y);
	sprite.setPosition(body->GetPosition().x * 30.0f,  body->GetPosition().y * 30.0f);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	window.draw(sprite);
}

b2ContactListener* Player::getContactListener() {
	return contactListener;
}