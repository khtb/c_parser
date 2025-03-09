#pragma once

#include <string>
#include <vector>


class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual void init() = 0;
	virtual void run(const std::vector<std::string>& arguments) = 0;
	// Abstract method for command auto-completion
	virtual void finalize() = 0;
	virtual std::string getName() const = 0;

protected:
	std::vector<std::string> arguments = {"get_name"};
};

