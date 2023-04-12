#include "CommandEngine.hpp"
#include "CommandBase.hpp"
#include "utils.hpp"

#include <regex>
#include <iostream>

void CommandEngine::registerCommand(CommandBasePtr command)
{
	if (command) {
		_commandsList[command->name()] = command;
	}
}

void CommandEngine::executeString(std::string_view str) const
{
	std::vector<std::string_view> viewsList = utils::splitSV(str);

	std::smatch base_match;

	if (viewsList.empty()) return;

	const std::string firstStr = std::string(viewsList[0]);
	bool found = false;
	for (const auto& [key, cmd] : _commandsList) {
		if (std::regex_match(firstStr, base_match, cmd->regexToFind())) {
			found = true;
			try {
				if (cmd->parseArgs(str)) {
					cmd->execute();
				}
			}
			catch (const std::exception& ex) {
				std::cerr << ex.what() << std::endl;
			}
		}
	}
	
	if (!found) {
		std::cout << "Command not found" << std::endl;
	}
}
