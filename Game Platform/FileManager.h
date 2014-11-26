#pragma once

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class FileManager {
	public:
		FileManager();
		~FileManager();

		void LoadContent(const char* filename,
						 std::vector<std::vector<std::string>> &attributes,
						 std::vector<std::vector<std::string>> &contents);
	
	private:
		std::vector<std::string> tempAttributes;
		std::vector<std::string> tempContents;
		enum LoadState { ATTRIBUTES, CONTENTS, NONE };
		int state;
};