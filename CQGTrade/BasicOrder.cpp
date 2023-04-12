#include "BasicOrder.hpp"

BasicOrder::BasicOrder(TraderPtr traderPtr, OrderType type, size_t quantity, size_t price) :
	_traderPtr(traderPtr), _type(type), _quantity(quantity), _price(price)
{
	_timeCreated = std::chrono::system_clock::now();
}

size_t BasicOrder::price() const
{
	return _price;
}

Time_t BasicOrder::dateCreated() const
{
	return _timeCreated;
}

size_t BasicOrder::quantity() const
{
	return _quantity;
}

OrderType BasicOrder::type() const
{
	return _type;
}

OrderBasePtr BasicOrder::cloneByQuantity(size_t qunatity) const
{
	return std::make_shared<BasicOrder>(_traderPtr, 
		_type, qunatity, _price);
}

TraderPtr BasicOrder::trader() const
{
	return _traderPtr;
}
