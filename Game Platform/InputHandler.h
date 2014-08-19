/** InputHandler is a Singleton class **/
class InputHandler {
	public:
		static InputHandler& Instance() { static InputHandler instance; return instance; }
		int keyInput() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
				return 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
				return 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				return -1;
			}
		}

	private:
		InputHandler() {};
};