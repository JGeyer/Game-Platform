#pragma once

#include "BaseOverlay.h"
#include "Player.h"

class PauseOverlay : public BaseOverlay {
	public:
		PauseOverlay();
		
		void OpenAnimation(sf::RenderWindow &App);
		void CloseAnimation(sf::RenderWindow &App);
		void SetAnimationDelay(int delay);
		int GetAnimationDelay();
		ScreenState::SecondaryState Update(sf::Event event);
		void Draw(sf::RenderWindow &App);

	private:
		enum MenuState { RESUME, QUIT } menuState;
		sf::Texture textureLeft, textureRight, textureArrow;
		sf::Sprite spriteLeft, spriteRight, spriteArrow;
		sf::Font font;
		sf::Text uxSelect_Resume, uxSelect_Quit;
		int animationDelay;
};