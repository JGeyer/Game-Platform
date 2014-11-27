#pragma once

#include "BaseOverlay.h"
#include "Player.h"

class StatsOverlay : public BaseOverlay {
	public:
		StatsOverlay(Player* player);
			void SetupStatEntry(sf::RectangleShape* entry, sf::Vector2f size, float x, float y, sf::Text* entry_type, 
								sf::String entry_text, sf::Vector2f entry_position);

		void Update();
		void Draw(sf::RenderWindow &App);

	private:
		Player* player;
		sf::RectangleShape statOutline;
		sf::RectangleShape statEntry1, statEntry2, statEntry3;
		sf::Font font;
		sf::Text textHealth, textSpeed, textJump;
};