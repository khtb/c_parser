#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "ICmd.h"


class IApplication
{
public:
	IApplication(std::string name) : name(name) {}
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
	virtual std::string getName() const { return name; }
	virtual void executeCommand(std::string cmd, std::vector<std::string>& args)
	{
		// search for cmd string in commands list if avail
		// execute the command
		for (auto command : commands)
		{
			if (command->getName() == cmd)
			{
				command->execute();
			}
		}
	}

protected:
	std::vector<command*> commands = {};
	virtual void initCommands()  {
		for (auto cmd : commands)
		{
			commandRegistrar(cmd->getName());
		}
	};
	std::string name;
	std::vector<std::string> arguments = {};
	std::function <void(const std::string&)> commandRegistrar;
	std::function <void(const std::string&)> appPrompt;


};


 
