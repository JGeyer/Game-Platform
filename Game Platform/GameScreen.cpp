#include "GameScreen.h"

GameScreen::GameScreen() {
	screenState = ScreenState::State::GAME;

	SCALE = 30.0f;
	TIMESTEP = 1 / 60.0f;
	cameraManager = new CameraManager();
	contactListener = new ContactListener();
	fileManager = new FileManager();
	hudManager = new HudManager();

	player = new Player();
}

GameScreen::GameScreen(const GameScreen& copyGameloopManager) {
	SCALE = copyGameloopManager.SCALE;
	TIMESTEP = copyGameloopManager.TIMESTEP;
	cameraManager = new CameraManager();
	*cameraManager = *copyGameloopManager.cameraManager;
	contactListener = new ContactListener();
	*contactListener = *copyGameloopManager.contactListener;
	fileManager = new FileManager();
	*fileManager = *copyGameloopManager.fileManager;
	hudManager = new HudManager();
	*hudManager = *copyGameloopManager.hudManager;
	player = new Player();
	*player = *copyGameloopManager.player;
}

b2World GameScreen::CreateEnvironment() {
	b2Vec2 gravity(0.0f, 35.0f);

	//TextureBackground.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/background.png");
	//SpriteBackground.setTexture(TextureBackground);
	//SpriteBackground.setColor(sf::Color(255, 255, 255, 255));
	//SpriteBackground.setPosition(0.0f, 0.0f);

	return b2World(gravity);
}

void GameScreen::CreateLevel(char* lfpathname, b2World &world) {
	LevelManager::Instance().UnloadContent();
	LevelManager::Instance().LoadContent(lfpathname, world, fileManager);
}

void GameScreen::SetCamera(Player* player) {
	cameraManager->setCamera(player->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).x * 30.0f - 400, 
							 player->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).y * 30.0f - 400);
}

void GameScreen::Clean() {
	LevelManager::Instance().UnloadContent();
	TextureManager::Instance().UnloadContent();
	ObjectManager::Instance().UnloadContent();
	ConsumableManager::Instance().UnloadContent();
	EntityManager::Instance().UnloadContent();

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
}

ScreenState::State GameScreen::Pause(sf::RenderWindow &App) {
	MenuScreen* menuScreen = new MenuScreen();

	ScreenState::State currentState = ScreenState::State::MENU;
	while (currentState == ScreenState::State::MENU) {
		currentState = menuScreen->Run(App);
	}
	delete menuScreen;
	return currentState;
}

ScreenState::State GameScreen::Inventory(sf::RenderWindow &App) {
	InventoryScreen* inventoryScreen = new InventoryScreen(player->getPlayerInfo());

	ScreenState::State currentState = ScreenState::State::INVENTORY;
	while (currentState == ScreenState::State::INVENTORY) {
		currentState = inventoryScreen->Run(App);
	}
	delete inventoryScreen;
	return currentState;
}

ScreenState::State GameScreen::Run(sf::RenderWindow &App) {
	/** Generate world and player **/
	b2World world = CreateEnvironment();
	CreateLevel("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/LoadFiles/TestLevel2.lf", world);
	objects = LevelManager::Instance().getObjects();
	consumables = LevelManager::Instance().getConsumables();
	entities = LevelManager::Instance().getEntities();
	player = static_cast<Player*>(entities.at(0));

	/** Set Song **/
	SetMusic("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Music/Game.ogg");
	screenSong->play();

	/** Additional Game Setup **/
	App.setKeyRepeatEnabled(true);
	App.setView(cameraManager->getCamera());
	world.SetContactListener(contactListener);

	/** Game Loop **/
	sf::Event event;
	SetCamera(player);
	while (App.isOpen()) {
		while (App.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				Clean();
				return ScreenState::State::EXITED;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
				screenSong->stop();
				ScreenState::State state = Pause(App);
				if (state != ScreenState::State::GAME) {
					return state;
				}
				screenSong->play();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
				ScreenState::State state = Inventory(App);
				if (state != ScreenState::State::GAME) {
					return state;
				}
			}
			player->Update(event);
		}
		//Update Passives on Entities
		for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
			(*it)->UpdatePassive();
		}
		//Update HUD
		hudManager->Update(player);

		//World Step
		world.Step(TIMESTEP, 8, 3);
		
		//Draw
		Draw(App);
	}
	Clean();
	return ScreenState::State::EXITED;
}

void GameScreen::Draw(sf::RenderWindow &App) {
	//Clear Window
	App.clear(sf::Color::White);

	//Draw Background
	//App.setView(App.getDefaultView());
	//App.draw(SpriteBackground);

	//Reset Camera, and Set Modified View
	SetCamera(player);
	App.setView(cameraManager->getCamera());

	//Draw Objects
	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end();) {
		if ((*it)->GetIsDead()) {
			delete (*it);
			it = objects.erase(it);
		}
		else {
			(*it)->Draw(App);
			 ++it;
		}
	}

	//Draw Consumables
	for (std::vector<Consumable*>::iterator it = consumables.begin(); it != consumables.end();) {
		if ((*it)->GetIsDead()) {
			delete (*it);
			it = consumables.erase(it);
		}
		else {
			(*it)->Draw(App);
			 ++it;
		}
	}

	//Draw Entities
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end();) {
		if ((*it)->GetIsDead()) {
			delete (*it);
			it = entities.erase(it);
		}
		else {
			(*it)->Draw(App);
			 ++it;
		}
	}

	//Draw HUD
	App.setView(App.getDefaultView());
	hudManager->Draw(App);

	//Display
	App.display();
}