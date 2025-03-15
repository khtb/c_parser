#include "svdParser_IApp.h"
#include "ICmd.h"
#include <iostream>

extern void parseTest(void);
CMDParse svdParser_IApp::cmdParse;
CMDGetName svdParser_IApp::cmdGetName;
static std::vector<ICmd*> commands;

void svdParser_IApp::init()
{
	std::cout << "Initializing svdParser_IApp\n";
	commandRegistrar("parse");
	commandRegistrar("get_name");
	initCommands();
}

void svdParser_IApp::initCommands()
{
	commands.push_back(&cmdParse);
	commands.push_back(&cmdGetName);
}

void svdParser_IApp::run(const std::vector<std::string>& arguments)
{
	std::cout << "Running "<< name << "\n";
	commands[0]->execute();
	parseTest();
	appPrompt(name);

}


void svdParser_IApp::finalize()
{
	std::cout << "Finalizing "<< name << "\n";
}

void svdParser_IApp::executeCommand(std::string cmd, std::vector<std::string>& args)
{
	if (cmd != "")
	{
		std::cout << cmd << "args"<< std::endl;
	}
}



// const CMDParse svdParser_IApp::cmdParse;
// const CMDGetName svdParser_IApp::cmdGetName;
// const std::vector<ICmd*> svdParser_IApp::commands = { &svdParser_IApp::cmdParse, &svdParser_IApp::cmdGetName };

