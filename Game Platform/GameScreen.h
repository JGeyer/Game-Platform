#pragma once

#include "BaseScreen.h"
#include "MenuScreen.h"
#include "ContactListener.h"
#include "CameraManager.h"
#include "CreationManager.h"
#include "OverlaysInclude.h"

class GameScreen : public BaseScreen {
	public:
		GameScreen(b2World &newWorld);
		GameScreen(const GameScreen& copyGameloopManager);
		~GameScreen();

		ScreenState::PrimaryState Run(sf::RenderWindow &App);
			ScreenState::PrimaryState HandleInput(sf::RenderWindow &App, sf::Event event, Player* player);
				void InputPause(sf::RenderWindow &App);
				void InputInventory();
				void InputCrafting();
				void InputStats();
				void InputShooting(Player* player);
			void DrawOrDeleteElements(sf::RenderWindow &App);
			void DrawOverlays(sf::RenderWindow &App);

	private:
		float SCALE;
		float TIMESTEP;

		b2World& world;
		CameraManager* cameraManager;
		ContactListener* contactListener;

		bool isCrafting, isInventory, isPaused, isStats;
		InventoryOverlay* inventory;
		StatsOverlay* stats;
		HudOverlay* hud;
		PauseOverlay* pause;

		sf::Texture textureBackground;
		sf::Sprite spriteBackground;

		std::vector<Object*> objects;
		std::vector<Consumable*> consumables;
		std::vector<Entity*> entities;
		std::vector<Bullet*> bullets;
};