#pragma once

#include "IApplication.h"
#include "ICmd.h"



class svdParser_IApp : public IApplication
{
public:
	svdParser_IApp(std::string name ): IApplication (name) {};
	svdParser_IApp() : IApplication("svdParser") {};
	void init() ;
	void run(const std::vector<std::string>& arguments) override;
	void finalize() override;
	
	private:
	void initCommands() override;
};

