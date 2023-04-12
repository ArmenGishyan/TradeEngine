#include <iostream>
#include <string>


#include "App.hpp"
#include "CommandEngine.hpp"
#include "MakeOrderCommand.hpp"
#include "PrintTrades.hpp"

App::App()
{
	_commandEngine = std::make_unique<CommandEngine>();
	registerCommands();
}

void App::start() {
	std::string str;

	while (true) {
		std::getline(std::cin, str);

		if (str == "exit") {
			break;
		}
		_commandEngine->executeString(str);
	}
}

void App::registerCommands()
{
	_commandEngine->registerCommand(std::make_shared<MakeOrderCommand>());
	_commandEngine->registerCommand(std::make_shared<PrintTrades>());
}