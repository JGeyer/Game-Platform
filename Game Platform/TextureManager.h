#pragma once

#include <SFML/Graphics.hpp>

class TextureManager {
	public:
		static TextureManager &Instance();
		void LoadContent(std::string path, std::vector<std::vector<std::string>> textures);
		void UnloadContent();
		sf::Texture getTexture(std::string id);

	private:
		TextureManager() : textureLibrary() {};
		std::map<std::string, std::string> textureLibrary;
};