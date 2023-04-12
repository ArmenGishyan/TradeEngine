#pragma once

#include "Prototypes.hpp"
#include "OrderType.hpp"

class Trade {
public:
	Trade(TraderPtr, OrderType, size_t, size_t);

	size_t price() const;
	size_t quantity() const;
	OrderType type() const;

	TraderPtr trader() const;

private:
	TraderPtr _traderPtr;
	OrderType _type;
	size_t _quantity;
	size_t _price;
};