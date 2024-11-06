#include <iostream>
#include "mod1.h"
#include "mod2.h"
#include "FileScanner.h"
#include "spdlog/spdlog.h"


int main() {
	std::cout << "Hello, World!" << std::endl;
	std::vector<std::string> x ;
	Mod1* mod1 = new Mod1[2];
	mod1[0].callPrintMessage();
	spdlog::info("Welcome to spdlog!");
	std::string fileName =  "main.cpp";
	std::string dirPath = "/mnt/c/D_Drive/workset/EclipseProjects/ArmStm32F091/";
	// parseFile(fileName);
	FileScanner scanner(dirPath);
	x =	scanner.getFiles();
	spdlog::info("Number of files found: {}", x.size());
	return 0;
}




