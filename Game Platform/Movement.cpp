#include "Movement.h"

Object Movement::CreateGround(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position) {
	Box ground = Box(inputManager);
	ground.Initialize(world, b2_staticBody, b2Vec2(position.x / SCALE, position.y / SCALE), b2Vec2(800.0f, 16.0f), 0.0f, 0.2f);
	ground.LoadContent(texture, b2Vec2(400.0f, 8.0f));
	objects.push_back(ground);
	return ground;
}

Object Movement::CreateBox(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position) {
	Box box = Box(inputManager);
	box.Initialize(world, b2_dynamicBody, b2Vec2(position.x / SCALE, position.y / SCALE), b2Vec2(32.0f, 32.0f), 1.0f, 0.7f);
	box.LoadContent(texture, b2Vec2(16.0f, 16.0f));
	objects.push_back(box);
	return box;
}

Object Movement::CreateCircle(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position) {
	Circle circle = Circle(inputManager);
	circle.Initialize(world, b2_dynamicBody, b2Vec2(position.x / SCALE, position.y / SCALE), 0.5f, 1.0f, 0.7f);
	circle.LoadContent(texture, b2Vec2(16.0f, 16.0f));
	objects.push_back(circle);
	return circle;
}

Object Movement::CreateCharacter(InputManager inputManager, b2World& world, sf::Texture texture, b2Vec2 position) {
	Box character = Box(inputManager);
	character.Initialize(world, b2_dynamicBody, b2Vec2(position.x / SCALE, position.y / SCALE), b2Vec2(32.0f, 32.0f), 1.0f, 3.0f);
	character.LoadContent(texture, b2Vec2(16.0f, 16.0f));
	objects.push_back(character);
	return character;
}

bool Movement::MovementTest() {
	/** Window Preparation **/
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Window");
	window.setFramerateLimit(60);

	/** Texture Preparation **/
	sf::Texture groundTexture;
	sf::Texture boxTexture;
	sf::Texture circleTexture;
	groundTexture.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/ground.png");
	boxTexture.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/box.png");
	circleTexture.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/circle.png");

	/** World Preparation **/
	b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);
	CreateGround(inputManager, world, groundTexture, b2Vec2(400.0f, 500.0f));
	CreateBox(inputManager, world, boxTexture, b2Vec2(400.0f, 300.0f));
	CreateBox(inputManager, world, boxTexture, b2Vec2(100.0f, 100.0f));
	CreateCircle(inputManager, world, circleTexture, b2Vec2(310.0f, 400.0f));
	CreateBox(inputManager, world, boxTexture, b2Vec2(200.0f, 250.0f));

	Object character = CreateCharacter(inputManager, world, boxTexture, b2Vec2(600.0f, 400.0f));

	while (window.isOpen()) {
		/* When user left-mouse click, add box into world */
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
				it->Update(event);
			}
			inputManager.Update(event);
			if (inputManager.KeyPressed(sf::Keyboard::Key::Left)) {
				b2Vec2 vel = character.body->GetLinearVelocity();
				vel.x = -3.0f;
				character.body->SetAwake(true);
				character.body->SetLinearVelocity(vel);
			}
			if (inputManager.KeyPressed(sf::Keyboard::Key::Right)) {
				b2Vec2 vel = character.body->GetLinearVelocity();
				vel.x = 3.0f;
				character.body->SetAwake(true);
				character.body->SetLinearVelocity(vel);
			}
			if (inputManager.KeyPressed(sf::Keyboard::Key::Space)) {
				float impulse = character.body->GetMass() * 5;
				character.body->ApplyLinearImpulse(b2Vec2(0, -impulse), character.body->GetWorldCenter(), true);
			}
		}

		/* Simulate world */
		world.Step(TIMESTEP, 8, 3);
		
		window.clear(sf::Color::White);

		for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
			it->Draw(window);
		}
		//objects.remove_if(&Object::IsDead);

		window.display();
	}

	return true;
}