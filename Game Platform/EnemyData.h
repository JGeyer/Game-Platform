#pragma once

struct EnemyData {
	enum enemy_type {
		GRUNT
	} enemyType;
	enum enemy_rank {
		REGULAR,
		LEADER,
		CHAMPION,
		SUPREME,
		DIVINE
	} enemyRank;
};