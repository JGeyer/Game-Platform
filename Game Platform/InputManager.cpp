#include "InputManager.h"

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

void InputManager::Update(sf::Event event) {
	this->event = event;
}

bool InputManager::KeyPressed(sf::Keyboard::Key key) {
	if (event.key.code == key && event.type == sf::Event::KeyPressed) {
		return true;
	}
	return false;
}

bool InputManager::KeyPressed(std::vector<sf::Keyboard::Key> keys) {
	for (std::vector<sf::Keyboard::Key>::iterator it = keys.begin(); it != keys.end(); it++) {
		if (KeyPressed(*it)) {
			return true;
		}
	}
	return false;
}

bool InputManager::KeyReleased(sf::Keyboard::Key key) {
	if (event.key.code == key && event.type == sf::Event::KeyReleased) {
		return true;
	}
	return false;
}

bool InputManager::KeyReleased(std::vector<sf::Keyboard::Key> keys) {
	for (std::vector<sf::Keyboard::Key>::iterator it = keys.begin(); it != keys.end(); it++) {
		if (KeyReleased(*it)) {
			return true;
		}
	}
	return false;
}

bool InputManager::KeyDown(sf::Keyboard::Key key) {
	if (sf::Keyboard::isKeyPressed(key)) {
		return true;
	}
	return false;
}

bool InputManager::KeyDown(std::vector<sf::Keyboard::Key> keys) {
	for (std::vector<sf::Keyboard::Key>::iterator it = keys.begin(); it != keys.end(); it++) {
		if (sf::Keyboard::isKeyPressed(*it)) {
			return true;
		}
	}
	return false;
}