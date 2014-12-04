#pragma once

#include "Entity.h"
#include "EnemyInfo.h"

class Enemy : public Entity {
	public:
		Enemy(EnemyInfo::EnemyData::enemy_type type, EnemyInfo::EnemyData::enemy_rank rank);
		void Initialize(b2World& world, b2Vec2 position);
		void Update();

		EnemyInfo GetEnemyInfo();
		void IncrementHealth(int value);
		void DecrementHealth(int value);

	private:
		int movementCounter;
		b2Vec2 movementBoundaries;
		int tookDamage;
		b2PolygonShape shape;
		EnemyInfo cEnemyInfo;		
};