#pragma once

struct ScreenState {
	enum PrimaryState {
		BASE,
		MAIN_MENU,
		GAME_RUNNING,
		EXITED
	};
	enum SecondaryState {
		NONE,
		CRAFTING,
		INVENTORY,
		STATS,
		PAUSED,
		QUIT
	};
};