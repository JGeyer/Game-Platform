#pragma once

#include "BaseScreen.h"

class MenuScreen : public BaseScreen {
	public:
		MenuScreen();
		
		void OpenAnimation(sf::RenderWindow &App);
		void CloseAnimation(sf::RenderWindow &App);

		ScreenState::State Run(sf::RenderWindow &App);
		void Draw(sf::RenderWindow &App);

	private:
		enum MenuState { PLAY, EXIT } menuState;
		sf::Texture TextureLeft, TextureRight, TextureArrow;
		sf::Sprite SpriteLeft, SpriteRight, SpriteArrow;
		sf::Texture TextureInit;
		sf::Sprite SpriteInit;
		sf::Font Font;
		sf::Text uxSelect_Play, uxSelect_Exit;
	};