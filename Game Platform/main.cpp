#include "ScreensInclude.h"

int main(int argc, char** argv) {
	/** Game loop **/

	ScreenState::State screen = ScreenState::State::MENU;

	/** Window Preparation **/
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Window");
	App.setFramerateLimit(60);
	App.setMouseCursorVisible(false);

	MenuScreen menuScreen;
	GameScreen gameScreen;

	/** Main Loop **/
	while (screen != ScreenState::State::EXITED) {
		if (screen == ScreenState::State::MENU) {
			screen = menuScreen.Run(App);
		}
		if (screen == ScreenState::State::GAME) {
			screen = gameScreen.Run(App);
		}
	}

	return EXIT_SUCCESS;
}