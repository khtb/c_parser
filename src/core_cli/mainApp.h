#pragma once

#include "IApplication.h"
#include <string>
#include <vector>


class mainApp : public IApplication
{
public:
	mainApp(std::string name) : name(name) {}
	void init() override;
	void run(const std::vector<std::string>& arguments) override;
	void finalize() override;
	std::string getName() const override { return name; }
private:
	std::string name;
};