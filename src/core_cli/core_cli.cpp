#include "core_cli.h"
#include <iostream>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>

#include "regdApp.h"
#include "misc.h"

char **commandCompleter(const char *text, int start, int end);
// rl_compentry_func_t* commandEntryCompleter;
char* commandEntryCompleter(char *text, int state);//(char *text, int state);
void custom_display_matches(char**, int, int);

std::vector<std::string> crntCommandList;
const std::vector<std::string> stdCommandList = {"ping", "pwd", "ls", "cat", "exit"};

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

void CoreCLI::AppPropmt(const std::string &prompt)
{
	std::string app_prompt = prompt + "#";
	std::string command;
	while ((command = readline(app_prompt.c_str())) != "exit")
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
	app->setCommandRegistrar([this](const std::string &command)
							 { this->registerCommand(command); });
	app->setAppPrompt([this](const std::string &prompt)
					  { this->AppPropmt(prompt); });
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
	// rl_attempted_completion_function = &commandCompleter;
	rl_completion_entry_function = (rl_compentry_func_t*) &commandEntryCompleter;
	// rl_completion_display_matches_hook = &custom_display_matches;
	crntCommandList = stdCommandList;
}

char* commandEntryCompleter(char *text, int state)// [](const char *text, int state)
{
    static int index, length;
    if (state == 0) {
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
void custom_display_matches(char**x , int y , int z)
{
 	std::cout <<"avaialbe commands : "<< crntCommandList.size() << std::endl;
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
	if (cmd == "ping")
	{
		std::cout << "pong\n";
	}
	else if (cmd == "pwd")
	{
		system("pwd");
	}
	else if (cmd == "ls")
	{
		system("ls");
	}
	else if (cmd == "echo")
	{
		system("echo Hello World");
	}
	else if (cmd == "app1")
	{
		std::vector<std::string> args = {"arg1", "arg2"};
		mainApp appx("app1");
		runApp(&appx, args);
	}
	else if (cmd == "svd")
	{
		std::vector<std::string> args = {"arg1", "arg2"};
		svdParser_IApp appx;
		appx.setName("svdParser");
		runApp(&appx, args);
	}
	else if (cmd =="help")
	{
		std::cout << "Available commands: \n";
		for (const auto &cmd : crntCommandList)
		{
			std::cout << cmd << "\n";
		}
	}
	else if (cmd == "exit")
	{
		exit(0);
	}
	else
	{
		std::cout << "Unknown command: " << command << "\n";
	}
}