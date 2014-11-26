#include "MusicManager.h"

MusicManager &MusicManager::Instance() {
	static MusicManager instance;
	return instance;
}

void MusicManager::LoadContent(char* lfFilename, FileManager* fileManager) {
	this->lfFilename = lfFilename;
	std::vector<std::vector<std::string>> attributes, contents, songs;
	std::string path;

	// Load Attributes and Contents
	fileManager->LoadContent(lfFilename, attributes, contents);
	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i][0] == "path") {
			path = contents[i][0];
		}
		if (attributes[i][0] == "songs") {
			songs.push_back(contents[i]);
		}
	}

	MusicManager::Instance().clearMusicLibrary();

	sf::Music currentSong;
	for (int i = 0; i < songs.size(); i++) {
		currentSong.openFromFile(path + songs[i][1]);
		//musicLibrary.insert(currentSong);
	}
}

void MusicManager::UnloadContent() {
	lfFilename = "";
	musicLibrary.clear();
}

void MusicManager::clearMusicLibrary() {
	musicLibrary.clear();
}

//sf::Music MusicManager::GetSong(std::string id) {
	//return musicLibrary.find(id)->second;
//}