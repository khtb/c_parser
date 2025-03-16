#include <iostream>
#include "FileScanner.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include "svdParser.h"
#include <cstdlib>
#include <string>
#include "core_cli.h"
#include "ICmd.h"
#include "string_util.h"
using namespace std;





int main()
{
	cout << "Hello, World!" << std::endl;
	vector<std::string> x;
	spdlog::info("Welcome to spdlog!");
	string fileName = "main.cpp";
	// string dirPath = "/mnt/c/D_Drive/workset/EclipseProjects/ArmStm32F091";
	std::string dirPath = "/home/khtb/workset/ArmStm32F091/";
	// parseFile(fileName);
	FileScanner scanner(dirPath);
	std::vector<std::string> ext = {".c", ".h"};
	x = scanner.getFiles(ext);
	spdlog::info("Number of files found: {}", x.size());

	CoreCLI cli;
	cli.start();
	return 0;

}	



