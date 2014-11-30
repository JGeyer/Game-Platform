//#include <vld.h>
#include "ScreensInclude.h"

b2World CreateWorld() {
	b2Vec2 gravity(0.0f, 35.0f);
	return b2World(gravity);
}

void CreateLevel(char* levelPath, b2World &world) {
	CreationManager::Instance().UnloadContent();
	CreationManager::Instance().LoadContent(levelPath, world);
}

int main(int argc, char** argv) {
	/** Window Preparation **/
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "RotoType");
	App.setFramerateLimit(60);
	App.setMouseCursorVisible(true);
	
	/** Load All Level Creation Paths **/
	char* lfFilename = "Assets/LoadFiles/LevelList.lf";
	std::vector<std::vector<std::string>> attributes, contents;
	std::vector<char*> levelPaths;
	FileManager::Instance().LoadContent(lfFilename, attributes, contents);
	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i][0] == "LoadFiles") {
			levelPaths.push_back(&contents[i][0][0]);
		}
	}

	/** Main Loop **/
	ScreenState::PrimaryState screen = ScreenState::PrimaryState::MAIN_MENU;
	while (screen != ScreenState::PrimaryState::EXITED) {
		if (screen == ScreenState::PrimaryState::MAIN_MENU) {
			MenuScreen* menuScreen = new MenuScreen();
			screen = menuScreen->Run(App);
			delete menuScreen;
		}
		if (screen == ScreenState::PrimaryState::GAME_RUNNING) {
			b2World world = CreateWorld();
			CreateLevel(levelPaths[0], world);
			GameScreen* gameScreen = new GameScreen(world);
			screen = gameScreen->Run(App);
			delete gameScreen;
		}
	}
	levelPaths.clear();
	return EXIT_SUCCESS;
}