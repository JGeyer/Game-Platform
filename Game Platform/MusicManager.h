#include <SFML/Audio/Music.hpp>
#include <vector>
#include "FileManager.h"

class MusicManager {
	public:
		static MusicManager &Instance();
		void LoadContent(char* lfFilename, FileManager* fileManager);
		void UnloadContent();

		void clearMusicLibrary();

		//sf::Music GetSong(std::string id);

	private:
		MusicManager() : lfFilename(""), musicLibrary() {};
		char* lfFilename;
		std::vector<sf::Music> musicLibrary;

};