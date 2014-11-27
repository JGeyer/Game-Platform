#pragma once

struct PlayerInfo {
	int health;
	int max_health;
	float movement_speed, jump_speed;
	int footContacts;
	struct Inventory {
		int copper, iron, carbon, zinc;
	} inventory;

	PlayerInfo() {
		health = 100;
		max_health = 100;
		inventory.copper = 0;
		inventory.iron = 0;
		inventory.carbon = 0;
		inventory.zinc = 0;
		movement_speed = 6.0f;
		jump_speed = 16.0f;
		footContacts = 0;
	}
};