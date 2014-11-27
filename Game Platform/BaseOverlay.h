#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include "ScreenState.h"

class BaseOverlay {
	public:
		virtual void LoadContent() {};
		virtual void UnloadContent() {};
		virtual void Update() {};
		virtual void Draw(sf::RenderWindow &App) {};
};