#include <iostream>
#include "mod1.h"

void Mod1::callPrintMessage()
{
	printMessage();
}

void Mod1::printMessage()
{
	std::cout << "Hello, World from mod1" << std::endl;
}