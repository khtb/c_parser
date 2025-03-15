#pragma once

#include "IApplication.h"
#include <string>
#include <vector>


class mainApp : public IApplication
{
public:
	mainApp(std::string name) : IApplication(name) {}
	void init() override;
	void run(const std::vector<std::string>& arguments) override;
	void finalize() override;
	std::string getName() const override { return name; }
private:
	void initCommands() override {
		for (auto cmd : commands)
		{
			commandRegistrar(cmd->getName());
			std::cout << "overriden initCommands\n";
		}
	};
};