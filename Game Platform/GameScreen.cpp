#include "GameScreen.h"

GameScreen::GameScreen(b2World &newWorld) : world(newWorld) {
	pScreenState = ScreenState::PrimaryState::GAME_RUNNING;
	sScreenState = ScreenState::SecondaryState::NONE;

	SCALE = 30.0f;
	TIMESTEP = 1 / 60.0f;

	cameraManager = new CameraManager();
	contactListener = new ContactListener();

	isCrafting = false;
	isInventory = false;
	isPaused = false;
	isStats = false;
}

GameScreen::GameScreen(const GameScreen& copyGameloopManager) : world(copyGameloopManager.world) {
	pScreenState = copyGameloopManager.pScreenState;
	sScreenState = copyGameloopManager.sScreenState;

	SCALE = copyGameloopManager.SCALE;
	TIMESTEP = copyGameloopManager.TIMESTEP;

	cameraManager = new CameraManager();
	*cameraManager = *copyGameloopManager.cameraManager;
	contactListener = new ContactListener();
	*contactListener = *copyGameloopManager.contactListener;

	isCrafting = copyGameloopManager.isCrafting;
	isInventory = copyGameloopManager.isInventory;
	isPaused = copyGameloopManager.isPaused;
	isStats = copyGameloopManager.isStats;
}

GameScreen::~GameScreen() {
	CreationManager::Instance().UnloadContent();
	TextureManager::Instance().UnloadContent();

	delete inventory;
	delete hud;
	delete pause;
	delete stats;

	delete screenSong;

	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		delete (*it);
	}
	objects.clear();
	for (std::vector<Consumable*>::iterator it = consumables.begin(); it != consumables.end(); ++it) {
		delete (*it);
	}
	consumables.clear();
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		delete (*it);
	}
	entities.clear();

	delete cameraManager;
	delete contactListener;
}

ScreenState::PrimaryState GameScreen::Run(sf::RenderWindow &App) {
	// Generate World & Level within it
	objects = CreationManager::Instance().GetObjects(world);
	consumables = CreationManager::Instance().GetConsumables(world);
	entities = CreationManager::Instance().GetEntities(world);

	// Generate Player & Overlays
	Player* player = static_cast<Player*>(entities.at(0));
	player->SetMovementSpeed(9.0f);
	player->SetJumpSpeed(18.0f);
	inventory = new InventoryOverlay(player);
	stats = new StatsOverlay(player);
	hud = new HudOverlay(player);
	pause = new PauseOverlay();
	
	// Set Song
	SetMusic(CreationManager::Instance().GetSong("main"));
	screenSong->play();

	// Additional Game Setup
	App.setKeyRepeatEnabled(false);
	App.setView(cameraManager->GetCamera());
	world.SetContactListener(contactListener);
	cameraManager->SetCamera(player->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).x * 30.0f - 400, 
							 player->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).y * 30.0f - 400);

	// Game Loop
	sf::Event event;
	while (App.isOpen()) {
		// Handle Input
		while (App.pollEvent(event)) {
			pScreenState = HandleInput(App, event, player);
			if (pScreenState != ScreenState::PrimaryState::GAME_RUNNING) {
				screenSong->stop();
				return pScreenState;
			}
		}
		// World Step & Updates if not paused
		if (!isPaused) {
			// Update Passives on Entities
			for (std::vector<Entity*>::iterator eit = entities.begin(); eit != entities.end(); ++eit) {
				(*eit)->Update();
			}
			player->UpdatePassives();
			// Update Onscreen Bullets
			for (std::vector<Bullet*>::iterator bit = bullets.begin(); bit != bullets.end(); ++bit) {
				(*bit)->Update();
			}
			// Update Overlays (excluding pause)
			hud->Update();
			inventory->Update();
			//crafting->Update();
			stats->Update();

			// Execute World Step
			world.Step(TIMESTEP, 8, 3);
		}
		// Draw Background
		// App.setView(App.getDefaultView());
		// App.draw(SpriteBackground);

		// Reset Camera, and Set Modified View (fixed to player position)
		cameraManager->SetCamera(player->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).x * 30.0f - 400, 
								 player->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).y * 30.0f - 400);
		App.setView(cameraManager->GetCamera());

		// Draw or Delete Elements (depending on isDead status)
		DrawOrDeleteElements(App);

		// Set to draw relative to screen
		App.setView(App.getDefaultView());

		// Draw Overlays
		DrawOverlays(App);

		// Open Door Animation (if necessary)
		if (pause->GetAnimationDelay() > 0) {
			pause->OpenAnimation(App);
		}

		//Display
		App.display();
	}
	// Close gracefully if loop somehow terminated
	screenSong->stop();
	return ScreenState::PrimaryState::EXITED;
}

ScreenState::PrimaryState GameScreen::HandleInput(sf::RenderWindow &App, sf::Event event, Player* player) {
	if (event.type == sf::Event::Closed) {
		return ScreenState::PrimaryState::EXITED;
	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Key::A) {
			player->SetLeftPressed(false);
		}
		if (event.key.code == sf::Keyboard::Key::D) {
			player->SetRightPressed(false);
		}
	}
	if (event.type == sf::Event::KeyPressed) {
		if (isPaused) {
			sScreenState = pause->Update(event);
			if (sScreenState == ScreenState::SecondaryState::QUIT) {
				return ScreenState::PrimaryState::MAIN_MENU;
			}
			if (sScreenState != ScreenState::SecondaryState::PAUSED) {
				sScreenState = ScreenState::SecondaryState::NONE;
				isPaused = !isPaused;
				pause->SetAnimationDelay(25);
				screenSong->play();
			}
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
				InputPause(App);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
				InputInventory();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
				InputCrafting();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
				InputStats();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
				InputShooting(player);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				player->SetLeftPressed(true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				player->SetRightPressed(true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
				player->Jump();
			}
		}
	}
	return ScreenState::PrimaryState::GAME_RUNNING;
}

void GameScreen::InputPause(sf::RenderWindow &App) {
	sScreenState = ScreenState::SecondaryState::PAUSED;
	screenSong->pause();
	pause->CloseAnimation(App);
	isPaused = !isPaused;
}

void GameScreen::InputInventory() {
	if (!isInventory) {
		sScreenState = ScreenState::SecondaryState::INVENTORY;
	}
	else {
		sScreenState = ScreenState::SecondaryState::NONE;
	}
	isInventory = !isInventory;
	isCrafting = false;
	isStats = false;
}

void GameScreen::InputCrafting() {
	if (!isCrafting) {
		sScreenState = ScreenState::SecondaryState::CRAFTING;
	}
	else {
		sScreenState = ScreenState::SecondaryState::NONE;
	}
	isCrafting = !isCrafting;
	isInventory = false;
	isStats = false;
}

void GameScreen::InputStats() {
	if (!isStats) {
		sScreenState = ScreenState::SecondaryState::STATS;
	}
	else {
		sScreenState = ScreenState::SecondaryState::NONE;
	}
	isStats = !isStats;
	isCrafting = false;
	isInventory = false;
}

void GameScreen::InputShooting(Player* player) {
	Bullet* bullet = new Bullet();
	Cell::Direction direction = player->direction;
	float x, y;
	if (direction == Cell::Direction::LEFT) {
		x = player->GetBody()->GetPosition().x - (35.0f / 30.0f);
		y = player->GetBody()->GetPosition().y;
	}
	else {
		x = player->GetBody()->GetPosition().x + (35.0f / 30.0f);
		y = player->GetBody()->GetPosition().y;
	}
	bullet->Initialize(world, b2Vec2(x, y), direction, 20.0f, player->GetPlayerInfo().damage);

	sf::Texture textureBullet;
	textureBullet.loadFromFile("Assets/Textures/bullet.png");
	bullet->LoadContent(textureBullet, b2Vec2(2.5f / 30.0f,  2.5f / 30.0f));
	bullets.push_back(bullet);
}

void GameScreen::DrawOrDeleteElements(sf::RenderWindow &App) {
	// Clear Window
	App.clear(sf::Color::White);

	// Draw Objects
	for (std::vector<Object*>::iterator oit = objects.begin(); oit != objects.end();) {
		if ((*oit)->GetIsDead()) {
			delete (*oit);
			oit = objects.erase(oit);
		}
		else {
			(*oit)->Draw(App);
			 ++oit;
		}
	}

	// Draw Consumables
	for (std::vector<Consumable*>::iterator cit = consumables.begin(); cit != consumables.end();) {
		if ((*cit)->GetIsDead()) {
			delete (*cit);
			cit = consumables.erase(cit);
		}
		else {
			(*cit)->Draw(App);
			 ++cit;
		}
	}

	// Draw Entities
	for (std::vector<Entity*>::iterator eit = entities.begin(); eit != entities.end();) {
		if ((*eit)->GetIsDead()) {
			delete (*eit);
			eit = entities.erase(eit);
		}
		else {
			(*eit)->Draw(App);
			 ++eit;
		}
	}

	// Draw Bullets
	for (std::vector<Bullet*>::iterator bit = bullets.begin(); bit != bullets.end();) {
		if ((*bit)->GetIsDead()) {
			delete (*bit);
			bit = bullets.erase(bit);
		}
		else {
			(*bit)->Draw(App);
			 ++bit;
		}
	}
}

void GameScreen::DrawOverlays(sf::RenderWindow &App) {
	// Draw HUD
	hud->Draw(App);
	
	// Draw Inventory (if selected)
	if (isInventory) {
		inventory->Draw(App);
	}
	
	// Draw Crafting (if selected)
	if (isCrafting) {
		//crafting->Draw(App);
	}

	// Draw Stats (if selected)
	if (isStats) {
		stats->Draw(App);
	}

	// Draw Pause Menu (if active)
	if (isPaused) {
		pause->Draw(App);
	}
}
