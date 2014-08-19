/** WindowHandler is a Singleton class **/
class WindowHandler {
	public:
		static WindowHandler& Instance() { static WindowHandler instance; return instance; }
		bool isOpen() { return window.isOpen(); }
		void close() { window.close(); }
		void clear(sf::Color color) { window.clear(color); }
		void display() { window.display(); }
		void draw(sf::Sprite sprite) { window.draw(sprite); }

	private:
		sf::RenderWindow window;
		WindowHandler() : window(sf::RenderWindow(sf::VideoMode(800, 600, 32), "Window")) { window.setFramerateLimit(60); };
};