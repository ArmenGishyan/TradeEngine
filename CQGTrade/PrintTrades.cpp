#include <iostream>

#include "PrintTrades.hpp"
#include "Market.hpp"
#include "Trade.hpp"
#include "Trader.hpp"

namespace {
	void sortTreads(std::vector<Trades>& tradeList) {
		for (auto& trade : tradeList) {
			std::sort(std::begin(trade), std::end(trade), [](std::shared_ptr<Trade> first, 
											std::shared_ptr<Trade> second) {
					if (first->trader()->ID() < second->trader()->ID())
						return true;
					else if (first->trader()->ID() == second->trader()->ID()) {
						if (first->type() < second->type()) {
							return true;
						}
						else if (first->type() == second->type()) {
							if (first->price() < second->price()) {
								return true;
							}
						}
					}
					return false;
			});

		}
	}
}

std::string PrintTrades::name() const
{
	return "print";
}

bool PrintTrades::execute()
{
	auto trades = Market::instance()->existingTrads();
	if (trades.empty()) {
		std::cout << "Trads not found" << std::endl;
		return false;
	}
	sortTreads(trades);
	for (const auto& trade : trades) {
		for (const auto& item : trade) {
			std::string type = item->type() == OrderType::Buy ? "+" : "-";
			std::cout << item->trader()->ID() << type << item->quantity() <<"@"<< item->price() << " ";
		}
		std::cout << std::endl;
	}
	return true;
}

bool PrintTrades::parseArgs(std::string_view command)
{
	return true;
}

std::regex PrintTrades::regexToFind() const
{
	return std::regex("print");
}
