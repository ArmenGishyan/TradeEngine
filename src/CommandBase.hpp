#pragma once 

#include <string_view>
#include <regex>

class CommandBase {
public:
	virtual ~CommandBase() = default;

	virtual std::string name() const = 0;
	virtual bool execute() = 0;
	virtual bool parseArgs(std::string_view command) = 0;
	virtual std::regex regexToFind() const = 0;
};
