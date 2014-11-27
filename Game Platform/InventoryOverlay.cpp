#include "InventoryOverlay.h"

InventoryOverlay::InventoryOverlay(Player* player) : BaseOverlay() {
	this->player = player;

	font.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Fonts/Arial.ttf");

	inventoryOutline.setSize(sf::Vector2f(200.0f, 150.0f));
	inventoryOutline.setFillColor(sf::Color(0, 0, 0, 100));
	inventoryOutline.setPosition(300.0f, 200.0f);

	sf::String invString;
	char invVal[10];

	sprintf_s(invVal, "%i", this->player->getPlayerInfo().inventory.copper);
	invString = sf::String(invVal);
	SetupInventoryEntry(&inventoryEntry1, sf::Vector2f(180.0f, 25.0f), 310.0f, 210.0f, &textCopper, "Copper: " + invString, sf::Vector2f(315.0f, 212.5f));

	sprintf_s(invVal, "%i", this->player->getPlayerInfo().inventory.iron);
	invString = sf::String(invVal);
	SetupInventoryEntry(&inventoryEntry2, sf::Vector2f(180.0f, 25.0f), 310.0f, 240.0f, &textIron, "Iron: " + invString, sf::Vector2f(315.0f, 242.5f));

	sprintf_s(invVal, "%i", this->player->getPlayerInfo().inventory.carbon);
	invString = sf::String(invVal);
	SetupInventoryEntry(&inventoryEntry3, sf::Vector2f(180.0f, 25.0f), 310.0f, 270.0f, &textCarbon, "Carbon: " + invString, sf::Vector2f(315.0f, 272.5f));

	sprintf_s(invVal, "%i", this->player->getPlayerInfo().inventory.zinc);
	invString = sf::String(invVal);
	SetupInventoryEntry(&inventoryEntry4, sf::Vector2f(180.0f, 25.0f), 310.0f, 300.0f, &textZinc, "Zinc: " + invString, sf::Vector2f(315.0f, 302.5f));
}

void InventoryOverlay::SetupInventoryEntry(sf::RectangleShape* entry, sf::Vector2f size, float x, float y, sf::Text* entry_type, 
										  sf::String entry_text, sf::Vector2f entry_position) {
	entry->setSize(size);
	entry->setFillColor(sf::Color(255, 255, 255, 100));
	entry->setPosition(x, y);
	entry_type->setFont(font);
    entry_type->setCharacterSize(20);
    entry_type->setString(entry_text);
    entry_type->setPosition(entry_position);
	entry_type->setColor(sf::Color(0, 0, 0, 100));
}

void InventoryOverlay::Update() {
	sf::String invString;
	char invVal[10];

	sprintf_s(invVal, "%i", player->getPlayerInfo().inventory.copper);
	invString = sf::String(invVal);
	textCopper.setString("Copper: " + invString);

	sprintf_s(invVal, "%i", player->getPlayerInfo().inventory.iron);
	invString = sf::String(invVal);
	textIron.setString("Iron: " + invString);

	sprintf_s(invVal, "%i", player->getPlayerInfo().inventory.carbon);
	invString = sf::String(invVal);
	textCarbon.setString("Carbon: " + invString);

	sprintf_s(invVal, "%i", player->getPlayerInfo().inventory.zinc);
	invString = sf::String(invVal);
	textZinc.setString("Zinc: " + invString);
}

void InventoryOverlay::Draw(sf::RenderWindow &App) {
	//Drawing
	App.draw(inventoryOutline);
	App.draw(inventoryEntry1);
	App.draw(textCopper);
	App.draw(inventoryEntry2);
	App.draw(textIron);
	App.draw(inventoryEntry3);
	App.draw(textCarbon);
	App.draw(inventoryEntry4);
	App.draw(textZinc);
}