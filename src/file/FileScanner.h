#pragma once


#include <iostream>
#include <vector>


class FileScanner
{
	public:
		explicit FileScanner(const std::string& dirPath);
		std::vector<std::string> getFiles() const;
	private:
		void findFiles(const std::string& dirFullpath,std::vector<std::string>& filesList) const;
		std::string dirPath;
		std::vector<std::string> files;
		
};