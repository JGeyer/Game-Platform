#pragma once

struct ContactUserData {
	enum Type {
		ANIMATE,
		INANIMATE,
		PLAYER,
		FOOT_SENSOR,
		MATERIAL,
		ENEMY
	} type;
	void* data;
};