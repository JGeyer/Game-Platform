#include "Enemy.h"

Enemy::Enemy(EnemyData::enemy_type type, EnemyData::enemy_rank rank) : Entity() {
	this->type = EntityData::entity_type::ENEMY;

	movementCounter = 0;
	movementBoundaries = b2Vec2(0, 100);
	direction = 0;

	cEnemyInfo.enemyInfo.enemyType = type;
	cEnemyInfo.enemyInfo.enemyRank = rank;
	cEnemyInfo.health = 100;
	cEnemyInfo.damage = 20;
	cEnemyInfo.movement_speed = 6.0f;
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
	b2Vec2 vel = body->GetLinearVelocity();
	
	if (direction == 0) {
		if (movementCounter < movementBoundaries.y) {
			movementCounter++;
			vel.x = cEnemyInfo.movement_speed;
		}
		else {
			direction = 1;
			vel.x = 0.0f;
		}
	}
	else {
		if (movementCounter > movementBoundaries.x) {
			movementCounter--;
			vel.x = -cEnemyInfo.movement_speed;
		}
		else {
			direction = 0;
			vel.x = 0.0f;
		}
	}
	body->SetLinearVelocity(vel);
	body->SetAwake(true);
}

Enemy::EnemyInfo Enemy::getEnemyInfo() {
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
	if (cEnemyInfo.health <= 0) {
		cEnemyInfo.health = 0;
		isDead = true;
	}
}