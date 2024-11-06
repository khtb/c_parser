#include <iostream>
#include "mod1.h"
#include "mod2.h"
#include "spdlog/spdlog.h"


int main() {
	std::cout << "Hello, World!" << std::endl;
	Mod1* mod1 = new Mod1[2];
	mod1[0].callPrintMessage();
	spdlog::info("Welcome to spdlog!");
	std::string fileName =  "main.cpp";
	parseFile(fileName);
	return 0;
}




