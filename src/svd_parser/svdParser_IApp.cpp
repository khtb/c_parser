#include "svdParser_IApp.h"
#include "ICmd.h"
#include <iostream>


//commands for svdParser_IApp
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

void svdParser_IApp::init()
{
	std::cout << "Initializing "<< this->name << std::endl;
	this->commands = {&cmdParse, &cmdgname};
	this->initCommands();
}


//test override
void svdParser_IApp::initCommands()
{
	for (auto cmd : this->commands)
	{
		commandRegistrar(cmd->getName());
	}
}

void svdParser_IApp::run(const std::vector<std::string>& arguments)
{
	std::cout << "Running "<< this->name << "\n";
	appPrompt(this->name);

}


void svdParser_IApp::finalize()
{
	std::cout << "Finalizing "<< name << "\n";
}


