#include "StatsOverlay.h"

StatsOverlay::StatsOverlay(Player* player) : BaseOverlay() {
	this->player = player;

	font.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Fonts/Arial.ttf");

	statOutline.setSize(sf::Vector2f(200.0f, 100.0f));
	statOutline.setFillColor(sf::Color(0, 0, 0, 100));
	statOutline.setPosition(300.0f, 250.0f);

	sf::String invString;
	char invVal[10];

	sprintf_s(invVal, "%i", this->player->getPlayerInfo().max_health);
	invString = sf::String(invVal);
	SetupStatEntry(&statEntry1, sf::Vector2f(180.0f, 25.0f), 310.0f, 260.0f, &textHealth, "Max HP: " + invString, sf::Vector2f(315.0f, 262.5f));

	sprintf_s(invVal, "%i", (int)this->player->getPlayerInfo().movement_speed);
	invString = sf::String(invVal);
	SetupStatEntry(&statEntry2, sf::Vector2f(180.0f, 25.0f), 310.0f, 290.0f, &textSpeed, "Movespeed: " + invString, sf::Vector2f(315.0f, 292.5f));

	sprintf_s(invVal, "%i", (int)this->player->getPlayerInfo().jump_speed);
	invString = sf::String(invVal);
	SetupStatEntry(&statEntry3, sf::Vector2f(180.0f, 25.0f), 310.0f, 320.0f, &textJump, "Jump Str: " + invString, sf::Vector2f(315.0f, 322.5f));
}

void StatsOverlay::SetupStatEntry(sf::RectangleShape* entry, sf::Vector2f size, float x, float y, sf::Text* entry_type, 
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

void StatsOverlay::Update() {
	sf::String invString;
	char invVal[10];

	sprintf_s(invVal, "%i", player->getPlayerInfo().max_health);
	invString = sf::String(invVal);
	textHealth.setString("Max HP: " + invString);

	sprintf_s(invVal, "%i", (int)player->getPlayerInfo().movement_speed);
	invString = sf::String(invVal);
	textSpeed.setString("Movespeed: " + invString);

	sprintf_s(invVal, "%i", (int)player->getPlayerInfo().jump_speed);
	invString = sf::String(invVal);
	textJump.setString("Jump Str: " + invString);
}

void StatsOverlay::Draw(sf::RenderWindow &App) {
	//Drawing
	App.draw(statOutline);
	App.draw(statEntry1);
	App.draw(textHealth);
	App.draw(statEntry2);
	App.draw(textSpeed);
	App.draw(statEntry3);
	App.draw(textJump);
}