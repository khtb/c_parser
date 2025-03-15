#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "ICmd.h"


class IApplication
{
public:
	virtual ~IApplication() {
		// Common cleanup code for all instances
		std::cout << "IApplication destructor called" << std::endl;
	}
	virtual void init() = 0;
	virtual void run(const std::vector<std::string>& arguments) = 0;
	virtual void finalize() = 0;

	virtual void setCommandRegistrar(std::function<void(const std::string&)> registrar) { commandRegistrar = registrar; };
	virtual void setAppPrompt(std::function<void(const std::string&)> prompt) { appPrompt = prompt; };
	// Abstract method for command auto-completion
	virtual std::string getName() const = 0;
	virtual void executeCommand(std::string cmd, std::vector<std::string>& args) = 0;

protected:
	void initCommands() {};
	std::vector<std::string> arguments = {"AppArg1, AppArg2"};
	std::function <void(const std::string&)> commandRegistrar;
	std::function <void(const std::string&)> appPrompt;


};


 
