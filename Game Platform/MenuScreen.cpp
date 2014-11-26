#include "MenuScreen.h"

MenuScreen::MenuScreen() {
	screenState = ScreenState::State::MENU;

	TextureInit.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/initializing.png");
	SpriteInit.setTexture(TextureInit);
	SpriteInit.setColor(sf::Color(255, 255, 255, 255));
	SpriteInit.setPosition(0.0f, 0.0f);

	TextureLeft.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/left_half_animation.png");
	SpriteLeft.setTexture(TextureLeft);
	SpriteLeft.setColor(sf::Color(255, 255, 255, 255));
	SpriteLeft.setPosition(-400.0f, 0.0f);

	TextureRight.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/right_half_animation.png");
	SpriteRight.setTexture(TextureRight);
	SpriteRight.setColor(sf::Color(255, 255, 255, 255));
	SpriteRight.setPosition(800.0f, 0.0f);
	
	TextureArrow.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/arrow.png");
	SpriteArrow.setTexture(TextureArrow);
	SpriteArrow.setColor(sf::Color(255, 255, 255, 255));
	SpriteArrow.setPosition(133.0f, 217.0f);

	Font.loadFromFile("Arial.ttf");

	uxSelect_Play.setFont(Font);
    uxSelect_Play.setCharacterSize(20);
    uxSelect_Play.setString("Play");
    uxSelect_Play.setPosition(sf::Vector2f( 145.0f, 210.0f ));
	uxSelect_Play.setColor(sf::Color(255, 255, 255, 255));

    uxSelect_Exit.setFont(Font);
    uxSelect_Exit.setCharacterSize(20);
    uxSelect_Exit.setString("Exit");
    uxSelect_Exit.setPosition(sf::Vector2f( 145.0f, 240.0f ));
	uxSelect_Exit.setColor(sf::Color(255, 255, 255, 255));
}

void MenuScreen::OpenAnimation(sf::RenderWindow &App) {
	int increment = 100;
	while (increment > 0) {
		SpriteLeft.move(-4.0f, 0.0f);
		SpriteRight.move(4.0f, 0.0f);
		App.clear();
		App.draw(SpriteInit);
		App.draw(SpriteLeft);
		App.draw(SpriteRight);
        App.display();
		--increment;
	}
}

void MenuScreen::CloseAnimation(sf::RenderWindow &App) {
	int increment = 100;
	while (increment > 0) {
		SpriteLeft.move(4.0f, 0.0f);
		SpriteRight.move(-4.0f, 0.0f);
		//App.clear();
		App.draw(SpriteLeft);
		App.draw(SpriteRight);
        App.display();
		--increment;
	}
}

ScreenState::State MenuScreen::Run(sf::RenderWindow &App) {
	sf::Event Event;
    menuState = PLAY;
	CloseAnimation(App);

	/** Set Song **/
	SetMusic("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Music/Menu.ogg");
	screenSong->play();

	while (App.isOpen()) {
        //Verifying events
        while (App.pollEvent(Event)) {
            // Window closed
            if (Event.type == sf::Event::Closed) {
                return ScreenState::State::EXITED;
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
					menuState = PLAY;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
					menuState = EXIT;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
					if (menuState == PLAY) {
						OpenAnimation(App);
						screenSong->stop();
						return ScreenState::State::GAME;
					}
					else {
						return ScreenState::State::EXITED;
					}
				}
            }
        }
        if (menuState == PLAY) {
            SpriteArrow.setPosition(133.0f, 217.0f);
        }
        else {
            SpriteArrow.setPosition(133.0f, 247.0f);
        }
		Draw(App);
    }

    //Never reaching this point normally, but just in case, exit the application
    return ScreenState::State::EXITED;
}

void MenuScreen::Draw(sf::RenderWindow &App) {
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(SpriteLeft);
	App.draw(SpriteRight);
	App.draw(SpriteArrow);
	App.draw(uxSelect_Play);
	App.draw(uxSelect_Exit);

	//Display
	App.display();
}