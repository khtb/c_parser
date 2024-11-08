#include <iostream>
#include "mod1.h"
#include "mod2.h"
#include "FileScanner.h"
#include "spdlog/spdlog.h"
#include <algorithm>

using namespace std;

int main()
{
	cout << "Hello, World!" << std::endl;
	vector<std::string> x;
	Mod1 *mod1 = new Mod1[2];
	mod1[0].callPrintMessage();
	spdlog::info("Welcome to spdlog!");
	string fileName = "main.cpp";
	string dirPath = "/mnt/c/D_Drive/workset/EclipseProjects/ArmStm32F091";
	// std::string dirPath = "/home/khtb/workset/ArmStm32F091/";
	// parseFile(fileName);
	FileScanner scanner(dirPath);
	std::vector<std::string> ext = {".ld"};
	x =	scanner.getFiles(ext);
	spdlog::info("Number of files found: {}", x.size());
	return 0;
}
