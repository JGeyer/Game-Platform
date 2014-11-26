#pragma once

struct PlayerInfo {
	int health;
	int copper, iron, carbon, zinc;
	float movement_speed, jump_speed;
	int footContacts;

	PlayerInfo() {
		health = 100;
		copper = 0;
		iron = 0;
		carbon = 0;
		zinc = 0;
		movement_speed = 6.0f;
		jump_speed = 16.0f;
		footContacts = 0;
	}
};