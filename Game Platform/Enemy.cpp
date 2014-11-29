#include "Enemy.h"

Enemy::Enemy(EnemyInfo::EnemyData::enemy_type type, EnemyInfo::EnemyData::enemy_rank rank) : Entity() {
	this->type = EntityData::entity_type::ENEMY;
	direction = Entity::Direction::LEFT;

	movementCounter = 0;
	movementBoundaries = b2Vec2(0, 100);

	cEnemyInfo = EnemyInfo(100, 20, 6.0f, type, rank);
}

void Enemy::Initialize(b2World& world, b2Vec2 position) {
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

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);

	b2Fixture* enemySensorFixture = body->CreateFixture(&fixtureDef);
	ContactUserData* cud = new ContactUserData();
	cud->type = ContactUserData::Type::ENEMY;
	cud->data = this;
	enemySensorFixture->SetUserData(cud);
}

void Enemy::Update(sf::Event event) {

}

void Enemy::UpdatePassive() {
	if (tookDamage > 0) {
		--tookDamage;
		if (tookDamage == 0) {
			sprite.setColor(sf::Color::White);
		}
	}

	b2Vec2 vel = body->GetLinearVelocity();
	
	if (direction == Entity::Direction::LEFT) {
		if (movementCounter < movementBoundaries.y) {
			movementCounter++;
			vel.x = cEnemyInfo.movement_speed;
		}
		else {
			direction = Entity::Direction::RIGHT;
			vel.x = 0.0f;
		}
	}
	else {
		if (movementCounter > movementBoundaries.x) {
			movementCounter--;
			vel.x = -cEnemyInfo.movement_speed;
		}
		else {
			direction = Entity::Direction::LEFT;
			vel.x = 0.0f;
		}
	}
	body->SetLinearVelocity(vel);
	body->SetAwake(true);
}

EnemyInfo Enemy::GetEnemyInfo() {
	return cEnemyInfo;
}

void Enemy::IncrementHealth(int value) {
	cEnemyInfo.health += value;
	if (cEnemyInfo.health > 100) {
		cEnemyInfo.health = 100;
	}
}

void Enemy::DecrementHealth(int value) {
	cEnemyInfo.health -= value;
	sprite.setColor(sf::Color::Red);
	tookDamage = 5;
	if (cEnemyInfo.health <= 0) {
		cEnemyInfo.health = 0;
		isDead = true;
	}
}