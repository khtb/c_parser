#pragma once

#include "IApplication.h"
#include "ICmd.h"



class svdParser_IApp : public IApplication
{
public:
	svdParser_IApp(std::string name ): name (name) {};
	svdParser_IApp() : name("svdParser") {};
	void init() ;
	void run(const std::vector<std::string>& arguments) override;
	void finalize() override;
	void setName(std::string name) { this->name = name; }
	std::string getName() const override { return name; }
	void executeCommand(std::string cmd, std::vector<std::string>& args) override;
	
	private:
	std::string name ;
	void initCommands();
};

