#pragma once
#include "IApplication.h"
#include "spdlog/spdlog.h"



class netIApp : public IApplication 
{
public:

	netIApp(std::string name) : name(name) {};
	netIApp() : name("netIApp") {};
	void init() override;
	void run(const std::vector<std::string>& arguments) override;
	void finalize() override;
	void setName(std::string name) { this->name = name; }
	std::string getName() const { return name; }

private:
	std::string name;

};