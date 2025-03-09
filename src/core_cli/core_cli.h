
#pragma once

#include <string>
#include <vector>
#include "IApplication.h"



class CoreCLI 
{
public:

	void start();
	void runApp(IApplication *app, std::vector<std::string> arguments);
private:
	void initCompletion();
	void executeCommand(const std::string &command);

};