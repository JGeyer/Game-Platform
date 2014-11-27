#pragma once

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class FileManager {
	public:
		static FileManager &Instance();
		void LoadContent(const char* filename,
						 std::vector<std::vector<std::string>> &attributes,
						 std::vector<std::vector<std::string>> &contents);
		void UnloadContent();
	
	private:
		FileManager() : tempAttributes(), tempContents(), state(2) {};
		std::vector<std::string> tempAttributes;
		std::vector<std::string> tempContents;
		enum LoadState { ATTRIBUTES, CONTENTS, NONE };
		int state;
};