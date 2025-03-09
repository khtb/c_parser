#include "mainApp.h"
#include <iostream>



void mainApp::init()
{
	std::cout << "Initializing mainApp\n";
}

void mainApp::run(const std::vector<std::string>& arguments)
{
	std::cout << "Running mainApp\n";
	for (const auto& arg : arguments)
	{
		std::cout << "Arguments" << arg << "\n";
	}
}


void mainApp::finalize()
{
	std::cout << "Finalizing mainApp\n";
}
