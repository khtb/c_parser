#include "svdParser_IApp.h"
#include <iostream>

extern void parseTest(void);
void svdParser_IApp::init()
{
	std::cout << "Initializing svdParser_IApp\n";
}


void svdParser_IApp::run(const std::vector<std::string>& arguments)
{
	std::cout << "Running "<< name << "\n";
	parseTest();
}


void svdParser_IApp::finalize()
{
	std::cout << "Finalizing "<< name << "\n";
}
