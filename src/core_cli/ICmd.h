#pragma once
#include <string>
#include <vector>


class ICmd
{
public:
	virtual std::string getName() const { return "command" ;}
};


class command : public ICmd
{
public:
	command(const std::string& name) : name(name) {}
	std::string getName() const override { return name; }	
	virtual void execute()  {};
	virtual ~command() {};
private:
	std::string name;
};
