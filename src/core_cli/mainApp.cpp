#include "mainApp.h"
#include <iostream>

// available commands for mainApp
class CmdPing : public command
{
public:
	CmdPing() : command("ping") {}
	void execute() override
	{
		std::cout << "poing " << std::endl;
	}
};

SysCmd cmdPwd = SysCmd("pwd");
SysCmd cmdLs = SysCmd("ls");
SysCmd cmddate = SysCmd("date");
CmdPing cmdPing = CmdPing();





void mainApp::init()
{
	this->commands = {&cmdPwd, &cmdLs, &cmdPing, &cmddate};
	std::cout << "Initializing "<< this->name << std::endl;
	this->initCommands();
}

void mainApp::run(const std::vector<std::string>& arguments)
{
	std::cout << "Running mainApp\n";
	for (const auto& arg : arguments)
	{
		std::cout << "Arguments" << arg << "\n";
	}
	appPrompt(this->name);

}


void mainApp::finalize()
{
	std::cout << "Finalizing mainApp\n";
}
