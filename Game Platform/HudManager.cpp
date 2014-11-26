#include "HudManager.h"
#include <string>

HudManager::HudManager() {
	font.loadFromFile("arial.ttf");

	InitializeText(&healthText, 16, sf::Text::Bold, 20.0f, 500.0f);
	InitializeBar(&healthBarOutline, sf::Vector2f(100.0f, 20.0f), sf::Color::White, sf::Color::Black, 3.0, 60.0f, 500.0f);
	InitializeBar(&healthBar, sf::Vector2f(100.0f, 20.0f), sf::Color::Green, sf::Color::Black, 2.0, 60.0f, 500.0f);

	InitializeText(&copperText, 14, sf::Text::Bold, 20.0f, 530.0f);
}

HudManager::HudManager(int health) {
	HudManager::HudManager();
	cScreenInfo.health = health;
}

void HudManager::Update(Player* player) {
	cScreenInfo.health = player->getPlayerInfo()->health;
}

void HudManager::Draw(sf::RenderWindow &window) {
	SetupHealth();

	window.draw(healthText);
	window.draw(healthBarOutline);
	window.draw(healthBar);
	window.draw(copperText);
}

void HudManager::InitializeText(sf::Text* text, int charSize, sf::Text::Style style, float x, float y) {
	text->setFont(font);
	text->setCharacterSize(charSize);
	text->setStyle(style);
	text->move(x, y);
}

void HudManager::InitializeBar(sf::RectangleShape* bar, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, float borderThickness, float x, float y) {
	bar->setSize(size);
	bar->setFillColor(fillColor);
	bar->setOutlineColor(outlineColor);
	bar->setOutlineThickness(borderThickness);
	bar->setPosition(x, y);
}

void HudManager::SetupHealth() {
	healthText.setString("HP: ");
	if (cScreenInfo.health < 25) {
		healthText.setColor(sf::Color::Red);
		healthBar.setFillColor(sf::Color::Red);
	}
	else if (cScreenInfo.health < 50) {
		healthText.setColor(sf::Color::Yellow);
		healthBar.setFillColor(sf::Color::Yellow);
	}
	else { // HP > 50
		healthText.setColor(sf::Color::Green);
		healthBar.setFillColor(sf::Color::Green);
	}
	healthBar.setSize(sf::Vector2f(static_cast<float>(cScreenInfo.health), 20.0f));
}