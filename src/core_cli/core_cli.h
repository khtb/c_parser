
#pragma once

#include <string>
#include <vector>
#include "IApplication.h"



class CoreCLI 
{
public:
	// CoreCLI() : currentApp(nullptr) {};
	CoreCLI() {};
	void start();
	void runApp(IApplication *app, std::vector<std::string> arguments);
	void registerCommand(const std::string& command);
	void AppPropmt(const std::string& prompt);


private:
	void initCompletion();
	// IApplication* currentApp;
	void executeCommand(const std::string &command);
	void resetCommandList();

};