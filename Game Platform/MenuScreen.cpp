#include "MenuScreen.h"

MenuScreen::MenuScreen() {
	pScreenState = ScreenState::PrimaryState::MAIN_MENU;
	sScreenState = ScreenState::SecondaryState::NONE;
	menuState = MenuScreen::MenuState::PLAY;

	textureInit.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Textures/initializing.png");
	spriteInit.setTexture(textureInit);
	spriteInit.setColor(sf::Color(255, 255, 255, 255));
	spriteInit.setPosition(0.0f, 0.0f);

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

	uxSelect_Play.setFont(font);
    uxSelect_Play.setCharacterSize(20);
    uxSelect_Play.setString("Play");
    uxSelect_Play.setPosition(sf::Vector2f( 145.0f, 210.0f ));
	uxSelect_Play.setColor(sf::Color(255, 255, 255, 255));

    uxSelect_Exit.setFont(font);
    uxSelect_Exit.setCharacterSize(20);
    uxSelect_Exit.setString("Exit");
    uxSelect_Exit.setPosition(sf::Vector2f( 145.0f, 240.0f ));
	uxSelect_Exit.setColor(sf::Color(255, 255, 255, 255));
}

MenuScreen::~MenuScreen() {
	delete screenSong;
}

void MenuScreen::OpenAnimation(sf::RenderWindow &App) {
	int increment = 100;
	while (increment > 0) {
		spriteLeft.move(-4.0f, 0.0f);
		spriteRight.move(4.0f, 0.0f);
		App.clear();
		App.draw(spriteInit);
		App.draw(spriteLeft);
		App.draw(spriteRight);
        App.display();
		--increment;
	}
}

void MenuScreen::CloseAnimation(sf::RenderWindow &App) {
	int increment = 100;
	while (increment > 0) {
		spriteLeft.move(4.0f, 0.0f);
		spriteRight.move(-4.0f, 0.0f);
		App.draw(spriteLeft);
		App.draw(spriteRight);
        App.display();
		--increment;
	}
}

ScreenState::PrimaryState MenuScreen::Run(sf::RenderWindow &App) {
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
                return ScreenState::PrimaryState::EXITED;
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
						return ScreenState::PrimaryState::GAME_RUNNING;
					}
					else {
						return ScreenState::PrimaryState::EXITED;
					}
				}
            }
        }
        if (menuState == PLAY) {
            spriteArrow.setPosition(133.0f, 217.0f);
        }
        else {
            spriteArrow.setPosition(133.0f, 247.0f);
        }
		Draw(App);
    }

    //Never reaching this point normally, but just in case, exit the application
    return ScreenState::PrimaryState::EXITED;
}

void MenuScreen::Draw(sf::RenderWindow &App) {
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(spriteLeft);
	App.draw(spriteRight);
	App.draw(spriteArrow);
	App.draw(uxSelect_Play);
	App.draw(uxSelect_Exit);

	//Display
	App.display();
}