#include <iostream>
#include "mod1.h"
#include "mod2.h"
#include "FileScanner.h"
#include "spdlog/spdlog.h"
#include <algorithm>
// #include "tinyxml2.h"
#include "svdParser.h"

using namespace std;

int main()
{
	cout << "Hello, World!" << std::endl;
	vector<std::string> x;
	Mod1 *mod1 = new Mod1[2];
	mod1[0].callPrintMessage();
	spdlog::info("Welcome to spdlog!");
	string fileName = "main.cpp";
	// string dirPath = "/mnt/c/D_Drive/workset/EclipseProjects/ArmStm32F091";
	std::string dirPath = "/home/khtb/workset/ArmStm32F091/";
	// parseFile(fileName);
	FileScanner scanner(dirPath);
	std::vector<std::string> ext = {".c", ".h"};
	x =	scanner.getFiles(ext);
	spdlog::info("Number of files found: {}", x.size());
	SVDParser parser("dummy_svd_file.svd");	
	parser.parse();
	std::vector<Peripheral> peripherals = parser.getPeripherals();
	for (Peripheral peripheral : peripherals)
	{
		spdlog::info("Peripheral name: {}", peripheral.getName());
		spdlog::info("Peripheral base address: {:#x}", peripheral.getBaseAddress());
		for ( const Register &reg : peripheral.getRegisters())
		{
			spdlog::info("Register name: {}", reg.getName());
			spdlog::info("Register address offset: {}", reg.getAddressOffset());
			spdlog::info("Register size: {}", reg.getSize());
		}
	}
	return 0;
}
