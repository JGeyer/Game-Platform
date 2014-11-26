#pragma once

struct ScreenState {
	enum State {
		NONE,
		MENU,
		GAME,
		INVENTORY,
		EXITED
	};
};