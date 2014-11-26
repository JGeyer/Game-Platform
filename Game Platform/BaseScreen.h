#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include "ScreenState.h"

class BaseScreen {
	public:
		virtual ScreenState::State Run (sf::RenderWindow &App) = 0;
		virtual void Draw(sf::RenderWindow &App) {};
		void SetMusic(std::string id) {
			screenSong = new sf::Music();
			screenSong->openFromFile(id);
			screenSong->setLoop(true);
		};

	protected:
		sf::Music* screenSong;
		ScreenState::State screenState;
};