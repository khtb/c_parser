#include "svdParser_IApp.h"
#include "ICmd.h"
#include <iostream>



class cmdParser : public command
{
public:
	cmdParser() : command("parser") {}
	void execute() override
	{
		std::cout << "Executing parse command\n";
	}
};

class cmdGetName : public command
{
public:
	cmdGetName() : command("khtb") {}
	void execute() override
	{
		std::cout << "Executing get_name command\n";
	}
};

cmdParser cmdParse = cmdParser();
cmdGetName cmdgname = cmdGetName();

std::array<command*,2> commands = {&cmdParse, &cmdgname};


void svdParser_IApp::init()
{
	std::cout << "Initializing svdParser_IApp\n";

	initCommands();
}

void svdParser_IApp::initCommands()
{
	for (auto cmd : commands)
	{
		commandRegistrar(cmd->getName());
		cmd->execute();
	}
}

void svdParser_IApp::run(const std::vector<std::string>& arguments)
{
	std::cout << "Running "<< name << "\n";
	appPrompt(name);

}


void svdParser_IApp::finalize()
{
	std::cout << "Finalizing "<< name << "\n";
}

void svdParser_IApp::executeCommand(std::string cmd, std::vector<std::string>& args)
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


