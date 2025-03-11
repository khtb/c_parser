#include "net_IApp.h"




void netIApp::init()
{
	spdlog::info ("Initializing netIApp\n");
	commandRegistrar("interface");
	commandRegistrar("get_name");
}


void netIApp::run(const std::vector<std::string>& arguments)
{
	spdlog::info ("Running netIApp\n");
	appPrompt(name);
}

void netIApp::finalize()
{
	spdlog::info ("Finalizing netIApp\n");
}
