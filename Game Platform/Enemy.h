#pragma once

#include "Entity.h"
#include "EnemyData.h"

class Enemy : public Entity {
	public:
		Enemy(EnemyData::enemy_type type, EnemyData::enemy_rank rank);
		void Initialize(b2World& world, b2Vec2 position);
		void Update(sf::Event event);
		void UpdatePassive();

		void IncrementHealth(int value);
		void DecrementHealth(int value);

	private:
		int movementCounter;
		b2Vec2 movementBoundaries;
		int direction;
		b2PolygonShape shape;

		struct EnemyInfo {
			EnemyData enemyInfo;
			int health;
			int damage;
			float movement_speed;
		} cEnemyInfo;

	public:
		EnemyInfo getEnemyInfo();
};