#include <iostream>

#include "PrintTrades.hpp"
#include "Market.hpp"
#include "Trade.hpp"
#include "Trader.hpp"

std::string PrintTrades::name() const
{
	return "print_trades";
}

bool PrintTrades::execute()
{
	auto trades = Market::instance()->existingTrads();
	for (const auto& trade : trades) {
		for (const auto& item : trade) {
			std::string type = item->type() == OrderType::Buy ? "+" : "-";
			std::cout << item->trader()->ID() << type << item->quantity() << item->price() << " ";
		}
		std::cout << std::endl;
	}
	return true;
}

bool PrintTrades::parseArgs(std::string_view command)
{
	return true;
}
