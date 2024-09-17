#include <iostream>
#include "mod1.h"

void Mod1::callPrintMessage()
{
	printMessage();
}

void Mod1::printMessage()
{
	std::cout << "Hello, World from mod1" << value << std::endl;
}

void Mod1(int x)
{
	// value = 0xAA;	
}