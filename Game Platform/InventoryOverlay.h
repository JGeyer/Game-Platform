#pragma once

#include "BaseOverlay.h"
#include "Player.h"

class InventoryOverlay : public BaseOverlay {
	public:
		InventoryOverlay(Player* player);
			void SetupInventoryEntry(sf::RectangleShape* entry, sf::Vector2f size, float x, float y, sf::Text* entry_type, 
									 sf::String entry_text, sf::Vector2f entry_position);

		void Update();
		void Draw(sf::RenderWindow &App);

	private:
		Player* player;
		sf::RectangleShape inventoryOutline;
		sf::RectangleShape inventoryEntry1, inventoryEntry2, inventoryEntry3, inventoryEntry4;
		sf::Font font;
		sf::Text textCopper, textIron, textCarbon, textZinc;
};