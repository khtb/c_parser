#include "FileScanner.h"
#include <dirent.h>   // POSIX directory handling
#include <sys/stat.h> // POSIX stat for checking file types
#include <iostream>
#include <vector>
#include <algorithm>
#include "spdlog/spdlog.h"

FileScanner::FileScanner(const std::string &dirPath) : dirPath(dirPath), scanned(false) {}
std::string getfindExtension(std::string fileName)
{
    std::string ext = "";
    if (fileName.find_last_of(".") != std::string::npos)
    {
        
        ext = fileName.substr(fileName.find_last_of("."),fileName.size());
    }
    return ext;
    
}
std::vector<std::string> FileScanner::getFiles() 
{
    // std::vector<std::string> files;
    if (!scanned)
    {
        findFiles(dirPath, allFiles);
    }
    return allFiles;
}


std::vector<std::string> FileScanner::getFiles(std::vector<std::string>& fileExtension)
{
    // std::vector<std::string> files;
    if (!scanned)
    {
        std::vector<std::string> extenstionList = {};
        findFiles(dirPath, allFiles);
    }

    std::vector <std::string> filteredFiles;
    for (const auto& file : allFiles)
    {
       std::string ext  = getfindExtension(file);
       if(ext != "")
       {
           if (std::find(fileExtension.begin(), fileExtension.end(), ext) != fileExtension.end())
           {
               filteredFiles.push_back(file);
           }
       }
    }

    return filteredFiles;;
}

void FileScanner::findFiles(const std::string& dirFullpath, std::vector<std::string>& filesList)
{
    DIR *dir = opendir(dirFullpath.c_str());
    if (!dir)
    {
        spdlog::error("Failed to open directory: {}", dirFullpath);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        std::string fileName = entry->d_name;
        std::string filePath = dirFullpath + "/" + fileName;

        if (fileName == "." || fileName == "..")
        {
            continue;
        }

        // spdlog::info("Found file: {}", filePath);

        struct stat fileStat;
        if (stat(filePath.c_str(), &fileStat) == 0)
        {
            if (S_ISDIR(fileStat.st_mode))
            {
                // Recursively search in subdirectory
                findFiles(filePath, filesList);
            }
            else if (S_ISREG(fileStat.st_mode))
            {
                filesList.push_back(filePath);
            }
        }
        else
        {
            spdlog::warn("Could not retrieve file information for: {}", filePath);
        }
    }
    closedir(dir);
}
