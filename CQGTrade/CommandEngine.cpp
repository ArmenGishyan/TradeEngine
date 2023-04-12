#include "CommandEngine.hpp"
#include "CommandBase.hpp"
#include "utils.hpp"

#include <regex>
#include <iomanip>
#include <iostream>

void CommandEngine::registerCommand(CommandBasePtr command)
{
	if (command) {
		_commandsList[command->name()] = command;
	}
}

void CommandEngine::executeString(std::string_view str)
{
	std::vector<std::string_view> viewsList = splitSV(str);

	const std::regex txt_regex("^T[0-9]+");
	std::smatch base_match;

	if (viewsList.empty()) return;
	
	// rework here
	const std::string val = std::string(viewsList[0]);
	if (std::regex_match(val, base_match, txt_regex))
	{
		auto item = _commandsList.find("add_trade");
		if (item != _commandsList.end()) {
			if (item->second->parseArgs(str)) {
				item->second->execute();
			}
		}
	}
	else if (viewsList[0] == "print_trades") {
		auto item = _commandsList.find("print_trades");
		if (item != _commandsList.end()) {
			if (item->second->parseArgs(str)) {
				item->second->execute();
			}
		}
	}
	else {
		std::cout << "Command not found";
	}
}
