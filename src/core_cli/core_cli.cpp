#include "core_cli.h"
#include <iostream>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>

#include "regdApp.h"
#include "misc.h"

char **commandCompleter(const char *text, int start, int end);
std::vector<std::string> stdCommandList = {"ping", "pwd", "ls", "cat", "exit"};

void CoreCLI::start()
{
	initCompletion();
	std::string prompt = "#";
	std::string command;
	while ((command = readline(prompt.c_str())) != "exit")
	{
		if (command.empty())
		{
			continue;
		}
		add_history(command.c_str());
		executeCommand(command);
	}
}
void CoreCLI::runApp(IApplication *app, std::vector<std::string> arguments)
{
	std::cout << "Running CoreCLI\n";
	app->init();
	app->run(arguments);
	app->finalize();
}

void CoreCLI::initCompletion()
{
	// Set the completion function to our command completer
	rl_attempted_completion_function = &commandCompleter;
}

char **commandCompleter(const char *text, int start, int end)
{
	std::vector<std::string> matches;
	// Loop through the command list and find commands that start with the typed text
	for (const auto &cmd : stdCommandList)
	{
		if (cmd.find(text) == 0)
		{ // Command starts with the entered text
			matches.push_back(cmd);
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
	if (command == "ping")
	{
		std::cout << "pong\n";
	}
	else if (command == "pwd")
	{
		system("pwd");
	}
	else if (command == "ls")
	{
		system("ls");
	}
	else if (command == "cat")
	{
		system("cat /etc/os-release");
	}
	else if (command == "app1")
	{
		std::vector<std::string> args = {"arg1", "arg2"};
		mainApp appx("app1");
		runApp(&appx, args);
	}
	else if (command == "svd")
	{
		std::vector<std::string> args = {"arg1", "arg2"};
		svdParser_IApp appx;
		appx.setName("svdParser");
		runApp(&appx, args);
	}
	else if (command == "exit")
	{
		exit(0);
	}
	else
	{
		std::cout << "Unknown command: " << command << "\n";
	}
}