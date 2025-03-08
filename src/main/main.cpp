#include <iostream>
#include "FileScanner.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include "svdParser.h"
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
using namespace std;

void executeCommand(const std::string &command)
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
	else if (command == "exit")
	{
		exit(0);
	}
	else
	{
		std::cout << "Unknown command: " << command << "\n";
	}
}


std::vector<std::string> commandList = {"ping", "pwd", "ls", "cat", "exit"};

char** commandCompleter(const char* text, int start, int end) {
    std::vector<std::string> matches;

    for (const auto& cmd : commandList) {
        if (cmd.find(text) == 0) {  // If the command starts with the entered text
            matches.push_back(cmd);
        }
    }

    // Allocate memory for Readline completion system
    char** result = nullptr;
    if (!matches.empty()) {
        result = (char**)malloc(sizeof(char*) * (matches.size() + 1));
        for (size_t i = 0; i < matches.size(); ++i) {
            result[i] = strdup(matches[i].c_str());
        }
        result[matches.size()] = nullptr;
    }

    return result;
}

int main()
{
	cout << "Hello, World!" << std::endl;
	vector<std::string> x;
	spdlog::info("Welcome to spdlog!");
	string fileName = "main.cpp";
	// string dirPath = "/mnt/c/D_Drive/workset/EclipseProjects/ArmStm32F091";
	std::string dirPath = "/home/khtb/workset/ArmStm32F091/";
	// parseFile(fileName);
	FileScanner scanner(dirPath);
	std::vector<std::string> ext = {".c", ".h"};
	x = scanner.getFiles(ext);
	spdlog::info("Number of files found: {}", x.size());

	rl_attempted_completion_function = commandCompleter; // Set tab completion function
	char *input;
	while ((input = readline("# ")) != nullptr)
	{
		if (input && *input)
		{
			add_history(input); // Add input to history
			executeCommand(input);
		}
		free(input); // Free the input buffer
	}
	return 0;
}
