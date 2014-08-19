#include <iostream>
#include <fstream>
#include <cstring>

class LoadManager {
	public:
		LoadManager() : filenameTextures("C:/Users/Jeff/Documents/GitHub/Game-Platform/Game Platform/Textures.lf") {};

	private:
		std::string filenameTextures;
};