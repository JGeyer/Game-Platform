#include "Player.h"

Player::Player() : Entity() {
	type = EntityData::entity_type::PLAYER;
	direction = Direction::RIGHT;

	leftPressed = false;
	leftHeld = false;
	rightPressed = false;
	rightHeld = false;
	hasControl = 0;
	hasImmunity = 0;
	cPlayerInfo = PlayerInfo();
}

void Player::Initialize(b2World& world, b2Vec2 position) {
	bodyDef.position = position;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	body = world.CreateBody(&bodyDef);

	Convert convert;
	b2Vec2 vs0, vs1, vs2, vs3;

	b2Vec2* vs = new b2Vec2[4];
	vs0 = convert.CoordPixelsToWorld(0, 50, 50.0f, 50.0f);
	vs1 = convert.CoordPixelsToWorld(0, 0, 50.0f, 50.0f);
	vs2 = convert.CoordPixelsToWorld(50, 0, 50.0f, 50.0f);
	vs3 = convert.CoordPixelsToWorld(50, 50, 50.0f, 50.0f);
	vs[0].Set(vs0.x, vs0.y);
	vs[1].Set(vs1.x, vs1.y);
	vs[2].Set(vs2.x, vs2.y);
	vs[3].Set(vs3.x, vs3.y);
	shape.Set(vs, 4);
	delete vs;

	b2PolygonShape footSensor;
	footSensor.SetAsBox(0.025f * 30.0f, 0.0033f * 30.0f, b2Vec2(0, 1.33f), 0);
	b2FixtureDef footFixtureDef;
	footFixtureDef.density = 1.0f;
	footFixtureDef.shape = &footSensor;
	footFixtureDef.isSensor = true;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);

	b2Fixture* playerSensorFixture = body->CreateFixture(&fixtureDef);
	ContactUserData* cud = new ContactUserData();
	cud->type = ContactUserData::Type::PLAYER;
	cud->data = this;
	playerSensorFixture->SetUserData(cud);

	b2Fixture* footSensorFixture = body->CreateFixture(&footFixtureDef);
	cud = new ContactUserData();
	cud->type = ContactUserData::Type::FOOT_SENSOR;
	cud->data = this;
	footSensorFixture->SetUserData(cud);
}

void Player::Update() {
	if (hasControl == 0) {
		if ((leftPressed && rightPressed) || (!leftPressed && !rightPressed)) {
			StopMove();
		}
		else {
			if (leftPressed) {
				Move(Cell::Direction::LEFT);
			}
			if (rightPressed) {
				Move(Cell::Direction::RIGHT);
			}
		}
	}
}

void Player::UpdatePassives() {
	if (hasImmunity > 0) {
		--hasImmunity;
		if (hasImmunity == 0) {
			sprite.setColor(sf::Color::White);
		}
	}
	if (hasControl > 0) {
		--hasControl;
		if (hasControl == 0) {
			b2Vec2 vel = body->GetLinearVelocity();
			vel.x = 0.0f;
			body->SetLinearVelocity(vel);
			body->SetAwake(true);
		}
	}
}

void Player::SetLeftPressed(bool state) {
	if (state) {
		if (leftPressed) {
			leftHeld = true;
		}
		else {
			leftPressed = true;
		}
	}
	else {
		leftPressed = false;
		leftHeld = false;
	}
}

void Player::SetRightPressed(bool state) {
	if (state) {
		if (rightPressed) {
			rightHeld = true;
		}
		else {
			rightPressed = true;
		}
	}
	else {
		rightPressed = false;
		rightHeld = false;
	}
}

void Player::Move(Cell::Direction direction) {
	this->direction = direction;
	float impulse_x = 0.0f;
	float desiredVel = 0.0f;

	float mass = body->GetMass();
	b2Vec2 vel = body->GetLinearVelocity();

	// X Velocity Impulse Calculation
	if (direction == Cell::Direction::LEFT && leftPressed) {
		sprite.setScale(-1, 1);
		desiredVel = -cPlayerInfo.movement_speed;
	}
	if (direction == Cell::Direction::RIGHT && rightPressed) {
		sprite.setScale(1, 1);
		desiredVel = cPlayerInfo.movement_speed;
	}
	float velChange = desiredVel - vel.x;
	impulse_x = mass * velChange;

	body->ApplyLinearImpulse(b2Vec2(impulse_x, 0.0f), body->GetWorldCenter(), true);
}

void Player::StopMove() {
	float mass = body->GetMass();
	b2Vec2 vel = body->GetLinearVelocity();
	float velChange = 0.0f - vel.x;
	float impulse_x = mass * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse_x, 0.0f), body->GetWorldCenter(), true);
}

void Player::Jump() {
	float impulse_y = 0.0f;
	float mass = body->GetMass();
	b2Vec2 vel = body->GetLinearVelocity();

	// Y Velocity Impulse Calculation (todo: identify true issue to AND statement)
	if ((cPlayerInfo.footContacts > 0) && (int)vel.y == 0) {
		impulse_y = -(mass * cPlayerInfo.jump_speed);
	}
	body->ApplyLinearImpulse(b2Vec2(0.0f, impulse_y), body->GetWorldCenter(), true);
}

PlayerInfo Player::GetPlayerInfo() {
	return cPlayerInfo;
}

void Player::Knockback(b2Vec2 otherPosition) {
	hasControl = 30;
	b2Vec2 vel = body->GetLinearVelocity();

	float diff_x = body->GetPosition().x - otherPosition.x;
	if (diff_x > 0) {
		vel.x = 8.0f;
	}
	else {
		vel.x = -8.0f;
	}
	vel.y = -8.0f;

	body->SetLinearVelocity(vel);
	body->SetAwake(true);
}

void Player::SetMovementSpeed(float speed) {
	cPlayerInfo.movement_speed = speed;
}

void Player::SetJumpSpeed(float speed) {
	cPlayerInfo.jump_speed = speed;
}

void Player::IncrementFootContacts() {
	cPlayerInfo.footContacts += 1;
}

void Player::DecrementFootContacts() {
	cPlayerInfo.footContacts -= 1;
}

void Player::IncrementHealth(int value) {
	cPlayerInfo.health += value;
	if (cPlayerInfo.health > 100) {
		cPlayerInfo.health = 100;
	}
}

void Player::DecrementHealth(int value) {
	if (hasImmunity == 0) {
		hasImmunity = 100;
		sprite.setColor(sf::Color::Red);
		cPlayerInfo.health -= value;
		if (cPlayerInfo.health <= 0) {
			cPlayerInfo.health = 0;
			//isDead = true;
		}
	}
}

void Player::AddResource(MaterialData::material_type material_type, int value) {
	if (material_type == MaterialData::material_type::COPPER) {
		cPlayerInfo.inventory.copper += value;
	}
	if (material_type == MaterialData::material_type::IRON) {
		cPlayerInfo.inventory.iron += value;
	}
	if (material_type == MaterialData::material_type::CARBON) {
		cPlayerInfo.inventory.carbon += value;
	}
	if (material_type == MaterialData::material_type::ZINC) {
		cPlayerInfo.inventory.zinc += value;
	}
}