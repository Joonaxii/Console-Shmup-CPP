#pragma once
#include <string>

class FilePath
{
public:

    FilePath(const char* inputPath);
    ~FilePath();

    std::string fullPath;
    std::string name;
    std::string extension;

};

