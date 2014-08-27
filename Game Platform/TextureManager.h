#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>

class TextureManager {
	public:
		static TextureManager &Instance();
		void setTextureLibrary(std::string path, std::vector<std::vector<std::string>> textures);
		void clearTextureLibrary();
		sf::Texture getTexture(std::string id);

	private:
		TextureManager() : textureLibrary() {};
		std::map<std::string, std::string> textureLibrary;
};