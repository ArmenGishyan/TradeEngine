#include "Trade.hpp"

Trade::Trade(TraderPtr traderPtr, OrderType type, size_t quantity, size_t price):
_traderPtr(traderPtr), _type(type), _quantity(quantity), _price(price)
{
}

size_t Trade::price() const
{
	return _price;
}

/*
Time_t Trade::dataCreated() const
{
	return Time_t();
}
*/
size_t Trade::quantity() const
{
	return _quantity;
}

OrderType Trade::type() const
{
	return _type;
}

TraderPtr Trade::trader() const
{
	return _traderPtr;
}
