#pragma once
class FileHelpers {

public:
static bool getAllFilesByExtension(const std::string path, std::vector<FilePath*>& files, const std::string extension);
};
