#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "FilePath.h"
#include "FileHelpers.h"
#include "windows.h"

bool FileHelpers::getAllFilesByExtension(const std::string path, std::vector<FilePath*>& files, const std::string extension) {

	if (!std::filesystem::is_directory(path)) 
	{ 
		const auto out = std::string("Path: '" + path + "' does not exist!\n");
		OutputDebugStringA(out.c_str());
		return false; 
	}

    auto dir = std::filesystem::directory_iterator(path);
	for (const auto& file : dir) {

		const auto temp = file.path().string();
		const std::string pth(temp.begin(), temp.end());

		FilePath* path = new FilePath(pth.c_str());
		if (std::strcmp(path->extension.c_str(), extension.c_str()) != 0) {

			//Not of given extension 
			delete path;
			continue;
		}
		files.push_back(path);
	}

	return true;
}