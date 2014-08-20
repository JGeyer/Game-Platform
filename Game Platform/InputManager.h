#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

class InputManager {
	public:
		InputManager();
		~InputManager();

		void Update(sf::Event event);
		
		bool KeyPressed(sf::Keyboard::Key key);
		bool KeyPressed(std::vector<sf::Keyboard::Key> keys);
		bool KeyReleased(sf::Keyboard::Key key);
		bool KeyReleased(std::vector<sf::Keyboard::Key> keys);
		bool KeyDown(sf::Keyboard::Key key);
		bool KeyDown(std::vector<sf::Keyboard::Key> keys);

	private:
		sf::Event event;
		
};

#endif