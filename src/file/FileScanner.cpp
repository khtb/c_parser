#include "FileScanner.h"
#include <dirent.h>    // POSIX directory handling
#include <sys/stat.h>  // POSIX stat for checking file types
#include <iostream>
#include <vector>
#include "spdlog/spdlog.h"

FileScanner::FileScanner(const std::string& dirPath) : dirPath(dirPath) {}

std::vector<std::string> FileScanner::getFiles() const {
    std::vector<std::string> files;
    findFiles(dirPath, files);
    return files;
}

void FileScanner::findFiles(const std::string& dirFullpath, std::vector<std::string>& filesList) const {
    DIR* dir = opendir(dirFullpath.c_str());
    if (!dir) {
        spdlog::error("Failed to open directory: {}", dirFullpath);
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string fileName = entry->d_name;
        std::string filePath = dirFullpath + "/" + fileName;

        if (fileName == "." || fileName == "..") {
            continue;
        }

        // spdlog::info("Found file: {}", filePath);

        struct stat fileStat;
        if (stat(filePath.c_str(), &fileStat) == 0) {
            if (S_ISDIR(fileStat.st_mode)) {
                // Recursively search in subdirectory
                findFiles(filePath, filesList);
            } else if (S_ISREG(fileStat.st_mode)) {
                // Check if it’s a .c or .h file
                if (fileName.size() >= 2) {
                    std::string extension = fileName.substr(fileName.size() - 2);
                    if (extension == ".c" || extension == ".h") {
                        filesList.push_back(filePath);
                    }
                }
            }
        } else {
            spdlog::warn("Could not retrieve file information for: {}", filePath);
        }
    }
    closedir(dir);
}