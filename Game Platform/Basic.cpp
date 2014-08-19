#include "Basic.h"

bool Basic::CreateGround(b2World& world, float x, float y) {
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	bodyDef.type = b2_staticBody;
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox((800.0f / 2) / SCALE, (16.0f / 2) / SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.0f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);

	return true;
}

bool Basic::CreateBox(b2World& world, int mouse_x, int mouse_y) {
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(mouse_x / SCALE, mouse_y / SCALE);
	bodyDef.type = b2_dynamicBody;
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox((32.0f / 2) / SCALE, (32.0f / 2) / SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);

	return true;
}

bool Basic::BasicTest() {
    /** Window Preparation **/
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Basic Test");
	Window.setFramerateLimit(60);

	/** World Preparation **/
	b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);
	CreateGround(world, 400.0f, 500.0f);

	/** Texture Preparation **/
	sf::Texture groundTexture;
	sf::Texture boxTexture;
	groundTexture.loadFromFile("./Assets/Textures/ground.png");
	boxTexture.loadFromFile("./Assets/Textures/box.png");

	while (Window.isOpen()) {
		/* When user left-mouse click, add box into world */
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int mouse_x = sf::Mouse::getPosition(Window).x;
			int mouse_y = sf::Mouse::getPosition(Window).y;
			CreateBox(world, mouse_x, mouse_y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			Window.close();
		}

		/* Simulate world */
		world.Step(TIMESTEP, 8, 3);

		Window.clear(sf::Color::White);
		for (b2Body* bodyIterator = world.GetBodyList(); bodyIterator != 0; 
			bodyIterator = bodyIterator->GetNext()) {
			if (bodyIterator->GetType() == b2_dynamicBody) {
				sf::Sprite boxSprite;
				boxSprite.setTexture(boxTexture);
				boxSprite.setOrigin(16.0f, 16.0f);
				boxSprite.setPosition(SCALE * bodyIterator->GetPosition().x, 
									  SCALE * bodyIterator->GetPosition().y);
				boxSprite.setRotation(bodyIterator->GetAngle() * 180 / b2_pi);
				Window.draw(boxSprite);
			}
			else {
				sf::Sprite groundSprite;
				groundSprite.setTexture(groundTexture);
				groundSprite.setOrigin(400.0f, 8.0f);
				groundSprite.setPosition(SCALE * bodyIterator->GetPosition().x, 
										 SCALE * bodyIterator->GetPosition().y);
				groundSprite.setRotation(bodyIterator->GetAngle() * 180 / b2_pi);
				Window.draw(groundSprite);
			}
		}
		Window.display();
	}

	return true;
}