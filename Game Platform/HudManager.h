#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Player.h"

class HudManager {
	public:
		HudManager();
		HudManager(int health);
		void Update(Player* player);
		void Draw(sf::RenderWindow &window);

		void InitializeText(sf::Text* text, int charSize, sf::Text::Style style, float x, float y);
		void InitializeBar(sf::RectangleShape* bar, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, float borderThickness, float x, float y);
		void SetupHealth();

	private:
		sf::Font font;
		sf::Text healthText;
		sf::Text copperText;
		sf::RectangleShape healthBarOutline;
		sf::RectangleShape healthBar;

		struct ScreenInfo {
			int health;

			ScreenInfo() {
				health = 100;
			}
		} cScreenInfo;
};