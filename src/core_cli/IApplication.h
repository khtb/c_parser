#pragma once

#include <string>
#include <vector>
#include <functional>

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual void init() = 0;
	virtual void run(const std::vector<std::string>& arguments) = 0;
	virtual void setCommandRegistrar(std::function<void(const std::string&)> registrar) { commandRegistrar = registrar; };
	virtual void setAppPrompt(std::function<void(const std::string&)> prompt) { appPrompt = prompt; };
	// Abstract method for command auto-completion
	virtual void finalize() = 0;
	virtual std::string getName() const = 0;

protected:
	std::vector<std::string> arguments = {"get_name"};
	std::function <void(const std::string&)> commandRegistrar;
	std::function <void(const std::string&)> appPrompt;
};

