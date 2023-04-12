#pragma once

#include "CommandBase.hpp"

class PrintTrades : public CommandBase {
public:
	std::string name() const override;
	bool execute() override;
	bool parseArgs(std::string_view command) override;

	std::regex regexToFind() const override;
};