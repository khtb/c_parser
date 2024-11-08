#pragma once


#include <iostream>
#include <vector>


class FileScanner
{
	public:
		explicit FileScanner(const std::string& dirPath);
		std::vector<std::string> getFiles(); 
		std::vector<std::string> getFiles(std::vector<std::string>& fileExtension);
	private:
		void findFiles(const std::string& dirFullpath,std::vector<std::string>& filesList);
		std::string dirPath;
		std::vector<std::string> allFiles;
		bool scanned;
		
};