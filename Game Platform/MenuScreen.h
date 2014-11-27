#pragma once

#include "BaseScreen.h"

class MenuScreen : public BaseScreen {
	public:
		MenuScreen();
		~MenuScreen();

		void OpenAnimation(sf::RenderWindow &App);
		void CloseAnimation(sf::RenderWindow &App);

		ScreenState::PrimaryState Run(sf::RenderWindow &App);
		void Draw(sf::RenderWindow &App);

	private:
		enum MenuState { PLAY, EXIT } menuState;
		sf::Texture textureLeft, textureRight, textureArrow;
		sf::Sprite spriteLeft, spriteRight, spriteArrow;
		sf::Texture textureInit;
		sf::Sprite spriteInit;
		sf::Font font;
		sf::Text uxSelect_Play, uxSelect_Exit;
	};