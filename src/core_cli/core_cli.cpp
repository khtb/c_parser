#include "core_cli.h"
#include <iostream>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <memory>
#include <vector>
#include <algorithm>
#include "regdApp.h"
#include "misc.h"

char **commandCompleter(const char *text, int start, int end);
char *commandEntryCompleter(const char *text, int state);
void custom_display_matches(char **, int, int);
static IApplication *currentApp = nullptr;
std::vector<std::string> crntCommandList;
const std::vector<std::string> stdCommandList = {"ping", "pwd", "ls", "cat", "exit"};

std::vector<std::unique_ptr<IApplication>> apps;

void CoreCLI::runPromptLoop(const std::string &prompt)
{
	std::string full_prompt = prompt + "#";
	std::string command;
	while ((command = readline(full_prompt.c_str())) != "exit")
	{
		if (command.empty())
		{
			continue;
		}
		add_history(command.c_str());
		executeCommand(command);
	}
}

void CoreCLI::start()
{
	initCompletion();
	apps.push_back(std::unique_ptr<IApplication>(new svdParser_IApp("svd")));
	apps.push_back(std::unique_ptr<IApplication>(new mainApp("main")));
	std::string prompt = "#";
	runPromptLoop(prompt);
}

void CoreCLI::AppPropmt(const std::string &prompt)
{
	std::string app_prompt = prompt + "#";
	std::string command;
	runPromptLoop(prompt);
}

void CoreCLI::runApp(IApplication *app, std::vector<std::string> arguments)
{
	std::cout << "Running CoreCLI\n";
	app->setCommandRegistrar([this](const std::string &command)
							 { this->registerCommand(command); });
	app->setAppPrompt([this](const std::string &prompt)
					  { this->AppPropmt(prompt); });
	currentApp = app;
	app->init();
	app->run(arguments);
	app->finalize();
	resetCommandList();
}

void CoreCLI::resetCommandList()
{
	crntCommandList = stdCommandList;
}

void CoreCLI::initCompletion()
{
	// Set the completion function to our command completer
	rl_completion_entry_function = &commandEntryCompleter;
	crntCommandList = stdCommandList;
}

char *commandEntryCompleter(const char *text, int state) // [](const char *text, int state)
{
	static int index, length;
	if (state == 0)
	{
		index = 0;
		length = strlen(text);
	}
	while (index < crntCommandList.size())
	{
		const std::string cmd = crntCommandList[index++];
		if (cmd.find(text) == 0)
		{
			return strdup(cmd.c_str());
		}
	}
	return nullptr;
}

void CoreCLI::registerCommand(const std::string &command)
{
	crntCommandList.push_back(command);
}

void custom_display_matches(char **x, int y, int z)
{
	std::cout << "avaialbe commands : " << crntCommandList.size() << std::endl;
	for (const auto &cmd : crntCommandList)
	{
		std::cout << cmd << "\n";
	}
}

char **commandCompleter(const char *text, int start, int end)
{
	std::vector<std::string> matches;
	if (text == nullptr || text[0] == '\0')
	{
		// Return all available commands in the current list
		matches = crntCommandList;
	}
	else
	{
		// Loop through the command list and find commands that start with the typed text
		for (const auto &cmd : crntCommandList)
		{
			if (cmd.find(text) == 0)
			{ // Command starts with the entered text
				matches.push_back(cmd);
			}
		}
	}

	// Allocate memory for the completion system (as Readline expects char**)
	char **result = nullptr;
	if (!matches.empty())
	{
		result = (char **)malloc(sizeof(char *) * (matches.size() + 1)); // +1 for NULL terminator
		for (size_t i = 0; i < matches.size(); ++i)
		{
			result[i] = strdup(matches[i].c_str()); // Allocate string memory
		}
		result[matches.size()] = nullptr; // Null-terminate the array
	}
	return result;
}

void CoreCLI::executeCommand(const std::string &command)
{
	std::string cmd = str_trim(command);
	size_t spaceIndex = cmd.find(" ");
	std::string cmdName = cmd.substr(0, spaceIndex);
	std::string cmdArgs = cmd.substr(spaceIndex + 1);
	std::vector<std::string> cmdArgsList;
	if (!cmdArgs.empty())
	{
		cmdArgsList.push_back(cmdArgs);
	}
	for (const auto &app : apps)
	{
		if (app->getName() == cmdName)
		{
			// std::vector<std::string> args = {"arg1", "arg2"};
			runApp(app.get(), cmdArgsList);
		}
	}
	if (cmd == "help")
	{
		std::cout << "Available Apps: " << std::endl;
		for (const auto &app : apps)
		{
			std::cout << app->getName() << std::endl;
		}
		std::cout << "=================== " << std::endl;
		std::cout << "Available commands: " << std::endl;
		for (const auto &cmd : crntCommandList)
		{
			std::cout << cmd << std::endl;
		}
	}
	else if (cmd == "exit")
	{
		exit(1);
	}
	else if (currentApp)
	{
		// if constexpr (std::is_base_of<IApplication, currentApp>::value)
		if (currentApp && dynamic_cast<IApplication *>(currentApp))
		{
			std::cout << "Running registered app " << currentApp->getName() << std::endl;
			currentApp->executeCommand(cmd, cmdArgsList);
		}
		else
		{
			std::cout << "No registered app to handle command." << std::endl;
		}
	}
	else
	{
		std::cout << "No application running to handle command." << std::endl;
	}
}