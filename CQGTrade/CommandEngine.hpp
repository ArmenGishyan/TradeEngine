#pragma once

#include <string_view>
#include <memory>
#include <unordered_map>

#include "Prototypes.hpp"

class CommandEngine {
public:
	void registerCommand(CommandBasePtr command);
	void executeString(std::string_view str);

private:
	std::unordered_map<std::string, CommandBasePtr> _commandsList;
};