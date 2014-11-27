#pragma once

#include <map>
#include <string>
#include <vector>

class MusicManager {
	public:
		static MusicManager &Instance();
		void LoadContent(std::string path, std::vector<std::vector<std::string>> songs);
		void UnloadContent();
		std::string getMusicPath(std::string id);

	private:
		MusicManager() : musicLibrary() {};
		std::map<std::string, std::string> musicLibrary;
};