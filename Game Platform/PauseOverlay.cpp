#include "PauseOverlay.h"

PauseOverlay::PauseOverlay() : BaseOverlay() {
	menuState = PauseOverlay::MenuState::RESUME;
	animationDelay = 0;

	textureLeft.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/left_half_animation.png");
	spriteLeft.setTexture(textureLeft);
	spriteLeft.setColor(sf::Color(255, 255, 255, 255));
	spriteLeft.setPosition(-400.0f, 0.0f);

	textureRight.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/right_half_animation.png");
	spriteRight.setTexture(textureRight);
	spriteRight.setColor(sf::Color(255, 255, 255, 255));
	spriteRight.setPosition(800.0f, 0.0f);
	
	textureArrow.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/arrow.png");
	spriteArrow.setTexture(textureArrow);
	spriteArrow.setColor(sf::Color(255, 255, 255, 255));
	spriteArrow.setPosition(133.0f, 217.0f);

	font.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Fonts/Arial.ttf");

	uxSelect_Resume.setFont(font);
    uxSelect_Resume.setCharacterSize(20);
    uxSelect_Resume.setString("Resume");
    uxSelect_Resume.setPosition(sf::Vector2f( 145.0f, 210.0f ));
	uxSelect_Resume.setColor(sf::Color(255, 255, 255, 255));

    uxSelect_Quit.setFont(font);
    uxSelect_Quit.setCharacterSize(20);
    uxSelect_Quit.setString("Quit");
    uxSelect_Quit.setPosition(sf::Vector2f( 145.0f, 240.0f ));
	uxSelect_Quit.setColor(sf::Color(255, 255, 255, 255));
}

void PauseOverlay::OpenAnimation(sf::RenderWindow &App) {
	if (animationDelay > 0) {
		spriteLeft.move(-16.0f, 0.0f);
		spriteRight.move(16.0f, 0.0f);
		App.draw(spriteLeft);
		App.draw(spriteRight);
		--animationDelay;
	}
}

void PauseOverlay::CloseAnimation(sf::RenderWindow &App) {
	int increment = 25;
	while (increment > 0) {
		spriteLeft.move(16.0f, 0.0f);
		spriteRight.move(-16.0f, 0.0f);
		App.draw(spriteLeft);
		App.draw(spriteRight);
        App.display();
		--increment;
	}
}

void PauseOverlay::SetAnimationDelay(int delay) {
	animationDelay = delay;
}

int PauseOverlay::GetAnimationDelay() {
	return animationDelay;
}

ScreenState::SecondaryState PauseOverlay::Update(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			menuState = RESUME;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			menuState = QUIT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
			if (menuState == RESUME) {
				return ScreenState::SecondaryState::NONE;
			}
			else {
				return ScreenState::SecondaryState::QUIT;
			}
		}
	}
	if (menuState == RESUME) {
		spriteArrow.setPosition(133.0f, 217.0f);
	}
	else {
		spriteArrow.setPosition(133.0f, 247.0f);
	}
	return ScreenState::SecondaryState::PAUSED;
}

void PauseOverlay::Draw(sf::RenderWindow &App) {
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(spriteLeft);
	App.draw(spriteRight);
	App.draw(spriteArrow);
	App.draw(uxSelect_Resume);
	App.draw(uxSelect_Quit);
}