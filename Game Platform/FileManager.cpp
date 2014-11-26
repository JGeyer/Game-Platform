#include "FileManager.h"

FileManager::FileManager() {
	state = NONE;
}

FileManager::~FileManager() {

}

void FileManager::LoadContent(const char* filename, 
	std::vector<std::vector<std::string>> &attributes,
	std::vector<std::vector<std::string>> &contents) {
	attributes.clear();
	contents.clear();

	std::ifstream openfile(filename);
	if (openfile.is_open()) {
		while (!openfile.eof()) {
			std::string line;
			std::getline(openfile, line);
			//line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
			if (line.find("Load=") != std::string::npos) {
				state = ATTRIBUTES;
				line.erase(0, line.find('=') + 1);
				tempAttributes.clear();
			}
			else {
				state = CONTENTS;
				tempContents.clear();
			}
			line.erase(std::remove(line.begin(), line.end(), '['), line.end());
			std::stringstream str(line);
			while (str) {
				std::getline(str, line, ']');
				if (line != "") {
					if (state == ATTRIBUTES) {
						tempAttributes.push_back(line);
					}
					else { // state == CONTENTS
						tempContents.push_back(line);
					}
				}
			}
			if (state == CONTENTS && tempContents.size() > 0) {
				attributes.push_back(tempAttributes);
				contents.push_back(tempContents);
			}
		}
	}
	else {
		//todo: else case
	}
}