#include "Movement.h"

bool Movement::CreateGround(b2World& world, sf::Texture texture, b2Vec2 position) {
	Box ground(world, texture, b2Vec2(400.0f, 8.0f), b2_staticBody, b2Vec2(position.x / SCALE, position.y / SCALE), b2Vec2(800.0f, 16.0f), 0.0f, 0.2f);
	objects.push_back(ground);
	return true;
}

bool Movement::CreateBox(b2World& world, sf::Texture texture, b2Vec2 position) {
	Box box(world, texture, b2Vec2(16.0f, 16.0f), b2_dynamicBody, b2Vec2(position.x / SCALE, position.y / SCALE), b2Vec2(32.0f, 32.0f), 1.0f, 0.7f);
	objects.push_back(box);
	return true;
}

bool Movement::CreateCircle(b2World& world, sf::Texture texture, b2Vec2 position) {
	Circle circle(world, texture, b2Vec2(16.0f, 16.0f), b2_dynamicBody, b2Vec2(position.x / SCALE, position.y / SCALE), 0.5f, 1.0f, 0.7f);
	objects.push_back(circle);
	return true;
}

bool Movement::MovementTest() {
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
	CreateGround(world, groundTexture, b2Vec2(400.0f, 500.0f));
	CreateBox(world, boxTexture, b2Vec2(400.0f, 300.0f));
	CreateBox(world, boxTexture, b2Vec2(100.0f, 100.0f));
	CreateCircle(world, circleTexture, b2Vec2(310.0f, 400.0f));
	CreateBox(world, boxTexture, b2Vec2(200.0f, 250.0f));
	CreateCircle(world, circleTexture, b2Vec2(300.0f, 0.0f));

	while (WindowHandler::Instance().isOpen()) {
		/* When user left-mouse click, add box into world */
		if (sf::Event::KeyPressed) {
			int code = InputHandler::Instance().keyInput();
			if (code == -1) {
				WindowHandler::Instance().close();
			}
		}

		/* Simulate world */
		world.Step(TIMESTEP, 8, 3);
		
		WindowHandler::Instance().clear(sf::Color::White);

		std::list<Object>::iterator i;
		for (i = objects.begin(); i != objects.end(); i++) {
			i->UpdateSprite();
			i->DrawSprite();
		}
		//objects.remove_if(&Object::IsDead);

		WindowHandler::Instance().display();
	}

	return true;
}