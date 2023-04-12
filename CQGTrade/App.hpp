#pragma once
#include <memory>
#include "Prototypes.hpp"

#include "CommandEngine.hpp"

class App {
public:
	App();
	void start();

private:
	void registerCommands();
	std::unique_ptr<CommandEngine> _commandEngine;
};