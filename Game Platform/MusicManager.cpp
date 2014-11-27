#include "MusicManager.h"

MusicManager &MusicManager::Instance() {
	static MusicManager instance;
	return instance;
}

void MusicManager::LoadContent(std::string path, std::vector<std::vector<std::string>> songs) {
	for (int i = 0; i < songs.size(); i++) {
		musicLibrary.insert(std::pair<std::string, std::string>(songs[i][0], path + songs[i][1]));
	}
}

void MusicManager::UnloadContent() {
	musicLibrary.clear();
}

std::string MusicManager::getMusicPath(std::string id) {
	return musicLibrary.find(id)->second;
}