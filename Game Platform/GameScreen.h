#pragma once

#include "BaseScreen.h"
#include "MenuScreen.h"
#include "InventoryScreen.h"
#include "ContactListener.h"
#include "CameraManager.h"
#include "HudManager.h"
#include "LevelManager.h"
#include "MusicManager.h"

class GameScreen : public BaseScreen {
	public:
		GameScreen();
		GameScreen(const GameScreen& copyGameloopManager);
		b2World CreateEnvironment();
		void CreateLevel(char* lfpathname, b2World &world);
		void SetCamera(Player* player);
		void Clean();

		ScreenState::State Pause(sf::RenderWindow &App);
		ScreenState::State Inventory(sf::RenderWindow &App);

		virtual ScreenState::State Run(sf::RenderWindow &App);
		virtual void Draw(sf::RenderWindow &App);

	private:
		float SCALE;
		float TIMESTEP;

		CameraManager* cameraManager;
		ContactListener* contactListener;
		FileManager* fileManager;
		HudManager* hudManager;

		Player* player;

		sf::Texture TextureBackground;
		sf::Sprite SpriteBackground;

		std::vector<Object*> objects;
		std::vector<Consumable*> consumables;
		std::vector<Entity*> entities;
};