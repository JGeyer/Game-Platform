#include "HudOverlay.h"

HudOverlay::HudOverlay(Player* player) {
	this->player = player;

	font.loadFromFile("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Assets/Fonts/Arial.ttf");

	InitializeText(&healthText, 16, sf::Text::Bold, 20.0f, 500.0f);
	InitializeBar(&healthBarOutline, sf::Vector2f(100.0f, 20.0f), sf::Color::White, sf::Color::Black, 3.0, 60.0f, 500.0f);
	InitializeBar(&healthBar, sf::Vector2f(100.0f, 20.0f), sf::Color::Green, sf::Color::Black, 2.0, 60.0f, 500.0f);
}

void HudOverlay::InitializeText(sf::Text* text, int charSize, sf::Text::Style style, float x, float y) {
	text->setFont(font);
	text->setCharacterSize(charSize);
	text->setStyle(style);
	text->move(x, y);
}

void HudOverlay::InitializeBar(sf::RectangleShape* bar, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, float borderThickness, float x, float y) {
	bar->setSize(size);
	bar->setFillColor(fillColor);
	bar->setOutlineColor(outlineColor);
	bar->setOutlineThickness(borderThickness);
	bar->setPosition(x, y);
}

void HudOverlay::Update() {
	int health = player->GetPlayerInfo().health;

	healthText.setString("HP: ");
	if (health < 25) {
		healthText.setColor(sf::Color::Red);
		healthBar.setFillColor(sf::Color::Red);
	}
	else if (health < 50) {
		healthText.setColor(sf::Color::Yellow);
		healthBar.setFillColor(sf::Color::Yellow);
	}
	else { // HP > 50
		healthText.setColor(sf::Color::Green);
		healthBar.setFillColor(sf::Color::Green);
	}
	healthBar.setSize(sf::Vector2f(static_cast<float>(health), 20.0f));
}

void HudOverlay::Draw(sf::RenderWindow &window) {
	window.draw(healthText);
	window.draw(healthBarOutline);
	window.draw(healthBar);
}