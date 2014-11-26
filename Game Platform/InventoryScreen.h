#pragma once

#include "BaseScreen.h"
#include "PlayerInfo.h"

class InventoryScreen : public BaseScreen {
	public:
		InventoryScreen(PlayerInfo* playerInfo);
		void SetupInventory(PlayerInfo* playerInfo);
		void SetupInventoryEntry(sf::RectangleShape* entry, sf::Vector2f size, float x, float y, sf::Text* entry_type, 
								 sf::String entry_text, sf::Vector2f entry_position);

		ScreenState::State Run(sf::RenderWindow &App);
		void Draw(sf::RenderWindow &App);

	private:
		sf::RectangleShape InventoryOutline;
		sf::RectangleShape InventoryEntry1, InventoryEntry2, InventoryEntry3, InventoryEntry4;
		sf::Font Font;
		sf::Text Copper, Iron, Carbon, Zinc;
};