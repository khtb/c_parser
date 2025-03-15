#pragma once

#include "IApplication.h"
#include "ICmd.h"


// class CMDParse;
// class CMDGetName;

//commmands

class CMDParse : public ICmd
{
public:
	CMDParse() = default;
	void execute() override
	{
		std::cout << "execute command I Parsing SVD file\n";
	}
private:
	std::string name =  "parse";
};

class CMDGetName : public ICmd
{
public:
	CMDGetName() = default;
	void execute() override
	{
		std::cout << "execute command I get_name\n";
	}
	void PrintPrivateFunction()
	{
		std::cout << "PrintPrivateFunction\n";
	}
private:	
	std::string name = "get_name";
};

class svdParser_IApp : public IApplication
{
public:
	svdParser_IApp(std::string name ): name (name) {};
	svdParser_IApp() : name("svdParser") {};
	void init() override;
	void run(const std::vector<std::string>& arguments) override;
	void finalize() override;
	void setName(std::string name) { this->name = name; }
	std::string getName() const { return name; }
	void executeCommand(std::string cmd, std::vector<std::string>& args) override;
	
	private:
	std::string name ;
	static CMDParse cmdParse;
	static CMDGetName cmdGetName;

	void initCommands();
};

