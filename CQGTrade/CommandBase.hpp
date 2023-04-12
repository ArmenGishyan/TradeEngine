#pragma once 

#include <string_view>

class CommandBase {
public:
	virtual std::string name() const = 0;
	virtual bool execute() = 0;
	virtual bool parseArgs(std::string_view command) = 0;
};
