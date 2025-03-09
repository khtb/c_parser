#include "svdParser_IApp.h"
#include <iostream>

extern void parseTest(void);
void svdParser_IApp::init()
{
	std::cout << "Initializing svdParser_IApp\n";
	commandRegistrar("parse");
	commandRegistrar("get_name");
	
}


void svdParser_IApp::run(const std::vector<std::string>& arguments)
{
	std::cout << "Running "<< name << "\n";
	parseTest();
	appPrompt(name);

}


void svdParser_IApp::finalize()
{
	std::cout << "Finalizing "<< name << "\n";
}
