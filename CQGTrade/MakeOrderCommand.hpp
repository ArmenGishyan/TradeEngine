#pragma once

#include "CommandBase.hpp"
#include "Prototypes.hpp"
#include "OrderType.hpp"

class MakeOrderCommand : public CommandBase {
public:
	std::string name() const override;
	bool execute() override;
	bool parseArgs(std::string_view command) override;

private:
	size_t _quantity;
	size_t _price;
	TraderPtr _trader;
	OrderType _type;
};