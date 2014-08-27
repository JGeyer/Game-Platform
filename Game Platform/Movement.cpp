#include "Movement.h"

Player Movement::CreatePlayer(InputManager inputManager, ContactListener *contactListener, b2World& world, sf::Texture texture, b2Vec2 position) {
	Player player = Player(inputManager, contactListener);
	player.Initialize(world, b2Vec2(position.x / SCALE, position.y / SCALE));
	player.LoadContent(texture, b2Vec2(40.0f, 40.0f));
	return player;
}

bool Movement::MovementTest() {
	/** Window Preparation **/
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Window");
	window.setFramerateLimit(60);

	/** World Preparation **/
	b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);

	/** Level Creation **/
	LevelManager::Instance().UnloadContent();
	objects = LevelManager::Instance().LoadContent("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/LoadFiles/TestLevel1.lf", world, fileManager, inputManager);

	/** Player Creation **/
	sf::Texture playerTexture = TextureManager::Instance().getTexture("character");
	Player player = CreatePlayer(inputManager, contactListener, world, playerTexture, b2Vec2(600.0f, 400.0f));
	world.SetContactListener(contactListener);

	/** Game Loop **/
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
				it->Update(event);
			}
			player.Update(event);
		}
		
		world.Step(TIMESTEP, 8, 3);
		
		window.clear(sf::Color::White);
		for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
			it->Draw(window);
		}
		player.Draw(window);
		window.display();
	}
	return true;
}