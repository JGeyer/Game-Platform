#include "InventoryScreen.h"

InventoryScreen::InventoryScreen(PlayerInfo* playerInfo) {
	screenState = ScreenState::State::INVENTORY;

	Font.loadFromFile("Arial.ttf");

	SetupInventory(playerInfo);
}

void InventoryScreen::SetupInventory(PlayerInfo* playerInfo) {
	InventoryOutline.setSize(sf::Vector2f(200.0f, 200.0f));
	InventoryOutline.setFillColor(sf::Color::Black);
	InventoryOutline.setPosition(300.0f, 200.0f);

	sf::String invString;
	char invVal[10];

	sprintf_s(invVal, "%i", playerInfo->copper);
	invString = sf::String(invVal);
	SetupInventoryEntry(&InventoryEntry1, sf::Vector2f(180.0f, 25.0f), 310.0f, 210.0f, &Copper, "Copper: " + invString, sf::Vector2f(315.0f, 212.5f));

	sprintf_s(invVal, "%i", playerInfo->iron);
	invString = sf::String(invVal);
	SetupInventoryEntry(&InventoryEntry2, sf::Vector2f(180.0f, 25.0f), 310.0f, 240.0f, &Iron, "Iron: " + invString, sf::Vector2f(315.0f, 242.5f));

	sprintf_s(invVal, "%i", playerInfo->carbon);
	invString = sf::String(invVal);
	SetupInventoryEntry(&InventoryEntry3, sf::Vector2f(180.0f, 25.0f), 310.0f, 270.0f, &Carbon, "Carbon: " + invString, sf::Vector2f(315.0f, 272.5f));

	sprintf_s(invVal, "%i", playerInfo->zinc);
	invString = sf::String(invVal);
	SetupInventoryEntry(&InventoryEntry4, sf::Vector2f(180.0f, 25.0f), 310.0f, 300.0f, &Zinc, "Zinc: " + invString, sf::Vector2f(315.0f, 302.5f));
}

void InventoryScreen::SetupInventoryEntry(sf::RectangleShape* entry, sf::Vector2f size, float x, float y, sf::Text* entry_type, 
										  sf::String entry_text, sf::Vector2f entry_position) {
	entry->setSize(size);
	entry->setFillColor(sf::Color::White);
	entry->setPosition(x, y);
	entry_type->setFont(Font);
    entry_type->setCharacterSize(20);
    entry_type->setString(entry_text);
    entry_type->setPosition(entry_position);
	entry_type->setColor(sf::Color(0, 0, 0, 255));
}

ScreenState::State InventoryScreen::Run(sf::RenderWindow &App) {
	sf::Event Event;

	while (App.isOpen()) {
        //Verifying events
        while (App.pollEvent(Event)) {
            // Window closed
            if (Event.type == sf::Event::Closed) {
                return ScreenState::State::EXITED;
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
					return ScreenState::State::GAME;
				}
            }
        }
		Draw(App);
    }

    //Never reaching this point normally, but just in case, exit the application
    return ScreenState::State::EXITED;
}

void InventoryScreen::Draw(sf::RenderWindow &App) {
	//Drawing
	App.draw(InventoryOutline);
	App.draw(InventoryEntry1);
	App.draw(Copper);
	App.draw(InventoryEntry2);
	App.draw(Iron);
	App.draw(InventoryEntry3);
	App.draw(Carbon);
	App.draw(InventoryEntry4);
	App.draw(Zinc);

	//Display
	App.display();
}