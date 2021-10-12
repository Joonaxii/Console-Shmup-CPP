#include "FilePath.h"
#include <algorithm>

FilePath::FilePath(const char* inputPath) {

    fullPath = std::string(inputPath);
    std::replace(fullPath.begin(), fullPath.end(), '\\', '/');

    std::string temp(fullPath);

    auto iter = fullPath.rfind('/');
    std::string tempN = iter < 0 ? std::string(fullPath.begin(), fullPath.end()) : temp.erase(0, iter + 1);

    iter = tempN.rfind('.');
    name = iter < 0 ? std::string(tempN.begin(), tempN.end()) : tempN.substr(0, iter);
    extension = iter < 0 ? std::string(0) : tempN.erase(0, iter);
}

FilePath::~FilePath() { }
