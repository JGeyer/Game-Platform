#pragma once

struct ContactUserData {
	enum Type {
		ANIMATE,
		INANIMATE,
		BULLET,
		PLAYER,
		FOOT_SENSOR,
		MATERIAL,
		ENEMY
	} type;
	void* data;
};