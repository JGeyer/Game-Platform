#pragma once

#include "BaseOverlay.h"
#include "Player.h"

class HudOverlay : public BaseOverlay {
	public:
		HudOverlay(Player* player);
			void InitializeText(sf::Text* text, int charSize, sf::Text::Style style, float x, float y);
			void InitializeBar(sf::RectangleShape* bar, sf::Vector2f size, sf::Color fillColor, 
							   sf::Color outlineColor, float borderThickness, float x, float y);

		void Update();
		void Draw(sf::RenderWindow &window);

	private:
		Player* player;
		sf::Font font;
		sf::Text healthText;
		sf::RectangleShape healthBarOutline;
		sf::RectangleShape healthBar;
};