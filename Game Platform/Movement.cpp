#include "Movement.h"

Player Movement::CreatePlayer(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position) {
	Player player = Player(inputManager);
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

	/** Read .lf files for load data **/
	FileManager file;
	std::vector<std::vector<std::string>> attributes;
	std::vector<std::vector<std::string>> contents;
	std::vector<std::vector<std::string>> textures;
	std::vector<std::vector<std::string>> objs;
	std::string path;
	file.LoadContent("./Assets/LoadFiles/TestLoad.lf", attributes, contents);
	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i][0] == "path") {
			path = contents[i][0];
		}
		if (attributes[i][0] == "texture") {
			textures.push_back(contents[i]);
		}
		if (attributes[i][0] == "object") {
			objs.push_back(contents[i]);
		}
	}

	/** Texture Preparation **/
	TextureManager::Instance().setTextureLibrary(path, textures);
	sf::Texture groundLargeTexture = TextureManager::Instance().getTexture("groundL");
	sf::Texture groundMediumTexture = TextureManager::Instance().getTexture("groundM");
	sf::Texture groundSmallTexture = TextureManager::Instance().getTexture("groundS");
	sf::Texture boxTexture = TextureManager::Instance().getTexture("box");
	sf::Texture circleTexture = TextureManager::Instance().getTexture("circle");
	sf::Texture playerTexture = TextureManager::Instance().getTexture("character");

	/** Body Creation Methods **/
	ObjectManager::Instance().setObjectLibrary(objs);
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "groundL1", groundLargeTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "groundM1", groundMediumTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "groundS1", groundSmallTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "groundS2", groundSmallTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "box1", boxTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "box2", boxTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "box3", boxTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "box4", boxTexture));
	objects.push_back(ObjectManager::Instance().createObject(inputManager, world, "circle1", circleTexture));

	/** Player Creation **/
	Player player = CreatePlayer(inputManager, world, playerTexture, b2Vec2(600.0f, 400.0f));

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