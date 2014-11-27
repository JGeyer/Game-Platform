#pragma once

struct EnemyInfo {
	struct EnemyData {
		enum enemy_type {
			NONE,
			GRUNT
		} enemyType;
		enum enemy_rank {
			UNRANKED,
			REGULAR,
			LEADER,
			CHAMPION,
			SUPREME,
			DIVINE
		} enemyRank;
	};
	
	int health;
	int damage;
	float movement_speed;
	EnemyData enemyData;

	EnemyInfo() {
		health = 0;
		damage = 0;
		movement_speed = 0;
		enemyData.enemyType = EnemyData::enemy_type::NONE;
		enemyData.enemyRank = EnemyData::enemy_rank::UNRANKED;
	}

	EnemyInfo(int health, int damage, float movement_speed, EnemyData::enemy_type type, EnemyData::enemy_rank rank) {
		this->health = health;
		this->damage = damage;
		this->movement_speed = movement_speed;
		enemyData.enemyType = type;
		enemyData.enemyRank = rank;
	}
};

